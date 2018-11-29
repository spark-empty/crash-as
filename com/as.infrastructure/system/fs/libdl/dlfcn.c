/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "dlfcn.h"
#include "elfloader.h"
#ifdef USE_SHELL
#include "shell.h"
#include "vfs.h"
#endif
#ifdef USE_PTHREAD
#include "pthread.h"
#include "semaphore.h"
#endif
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
#ifdef USE_SHELL
#ifdef USE_PTHREAD
struct dllParam
{
	int argc;
	char** argv;
	void* dll;
	ShellFuncT mentry;
};
#endif
#endif
/* ============================ [ DECLARES  ] ====================================================== */
#ifdef USE_SHELL
static int dllFunc(int argc, char* argv[]);
#endif
/* ============================ [ DATAS     ] ====================================================== */
#ifdef USE_SHELL
SHELL_CONST ShellCmdT dllCmd  = {
	dllFunc,
	0,256,
	"dll",
	"dll [path]",
	"load dll and run the code from the main entry\n",
	{NULL,NULL}
};
SHELL_CMD_EXPORT(dllCmd);

#ifdef USE_PTHREAD
static sem_t dllSem;
#endif
#endif
/* ============================ [ LOCALS    ] ====================================================== */
#ifdef USE_SHELL
#ifdef USE_PTHREAD
static void dllExit(void* arg)
{
	struct dllParam* param = arg;
	dlclose(param->dll);
	free(param);

#ifdef USE_PTHREAD_SIGNAL
	exit(0); /* in case of killed by others */
#endif
}
static void* dllMain(void* arg)
{
	void* r;
	struct dllParam* param = arg;

	pthread_cleanup_push(dllExit, arg);

	(void)sem_post(&dllSem);
	r = (void*)param->mentry(param->argc, param->argv);

	pthread_cleanup_pop(1);
#ifdef USE_PTHREAD_SIGNAL
	exit((int)r);
#endif
	return r;
}
#endif
static void* dllOpen(char* file)
{
	void* dll;
	char* rpath;
	char path[64];

	dll = dlopen(file, RTLD_NOW);
	if((NULL==dll) && ('/' != file[0]))
	{
		rpath = vfs_find(file);

		if(NULL == rpath)
		{
			snprintf(path, sizeof(path),"%s.dll", file);
			rpath = vfs_find(path);
		}

		if(NULL != rpath)
		{
			dll = dlopen(rpath, RTLD_NOW);
			free(rpath);
		}
	}

	return dll;
}
static int dllFunc(int argc, char* argv[])
{
	int r = 0;
	ShellFuncT mentry;
	void* dll;
#ifdef USE_PTHREAD
	int detachflag = 0;
#endif

	if(0 == strcmp(argv[0],"dll"))
	{
		argc --;
		argv++;
		if(0 == argc)
		{
			SHELL_printf("invalid args for dll\n");
			return -EINVAL;
		}
	}

#ifdef USE_PTHREAD
	if(0 == strcmp(argv[argc-1],"&"))
	{
		detachflag = 1;
		argc --;
		if(0 == argc)
		{
			SHELL_printf("invalid args for &\n");
			return -EINVAL;
		}
	}
#endif

	dll = dllOpen(argv[0]);
	if(NULL != dll)
	{
		mentry = dlsym(dll, "main");
		if(NULL != mentry)
		{
#ifdef USE_PTHREAD
			pthread_t thread;
			void* ret;
			struct dllParam* param;
			pthread_attr_t attr;
			struct sched_param sparam;
			int i;
			size_t sz;
			char* str;

			sz = 0;
			for(i=0;i<argc;i++)
			{
				sz += strlen(argv[i])+1;
			}

			param = malloc(sizeof(struct dllParam)+sz+(sizeof(char*)*argc));
			if(NULL != param)
			{
				param->argc = argc;
				param->argv = (char**)&param[1];
				str = ((void*)param->argv)+(sizeof(char*)*argc);
				for(i=0;i<argc;i++)
				{
					param->argv[i] = str;
					strcpy(str, argv[i]);
					str += strlen(argv[i])+1;
				}

				param->mentry = mentry;
				param->dll = dll;
				pthread_attr_init(&attr);
				sparam.sched_priority = OS_PTHREAD_PRIORITY/2; /* medium */

				pthread_attr_setschedparam(&attr, &sparam);
				if(detachflag)
				{
					pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
				}

				(void)sem_init(&dllSem, 0, 0);
			}
			if((NULL != param) && (0 == pthread_create(&thread, &attr, dllMain, param)))
			{
				/* make sure the dll thread started and the cleanup install */
				(void)sem_wait(&dllSem);
				if(!detachflag)
				{
					pthread_join(thread,&ret);

					r = (int)(unsigned long)ret;
				}
			}
			else
			{
				if(NULL != param)
				{
					free(param);
				}
				dlclose(dll);
				r = -ENOMEM;
			}
#else
			r = mentry(argc,argv);
			dlclose(dll);
#endif
		}
		else
		{
			SHELL_printf("no 'main' entry in dll\n");
			dlclose(dll);
		}
	}
	else
	{
		SHELL_printf("no command '%s'\n",argv[0]);
		r = -1;
	}
	return r;
}
#endif
/* ============================ [ FUNCTIONS ] ====================================================== */
void *dlopen(const char *filename, int flag)
{
	(void) flag; /* always RTLD_NOW */

	return ELF_Open(filename);
}

void *dlsym(void *handle, const char *symbol)
{
	return ELF_LookupSymbol(handle, symbol);
}

int dlclose(void *handle)
{
	return ELF_Close(handle);
}

