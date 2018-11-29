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
#if defined(__WINDOWS__) || defined(__LINUX__)
/* ============================ [ INCLUDES  ] ====================================================== */
#include <io.h>
#include <unistd.h>
#include <dirent.h>
#include "vfs.h"
#include "asdebug.h"

/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_HOFS 0
#define TO_HOFS_PATH(f) ( (((f)[5])=='/')? (&((f)[6])) : (&((f)[5])) )
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern const struct vfs_filesystem_ops hofs_ops;
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static VFS_FILE* host_fopen (const char *filename, const char *opentype)
{
	VFS_FILE *f;

	ASLOG(HOFS, "fopen(%s,%s)\n", filename, opentype);

	f = malloc(sizeof(VFS_FILE));
	if(NULL != f)
	{
		f->priv = (void*)fopen(TO_HOFS_PATH(filename), opentype);
		if (NULL == f->priv)
		{
			free(f);
			f = NULL;
		}
		else
		{
			f->fops = &hofs_ops;
		}
	}

	return f;
}

static int host_fclose (VFS_FILE* stream)
{
	int r;

	r = fclose((FILE*)(stream->priv));

	if (0 == r)
	{
		free(stream);
	}

	return r;
}

static int host_fread (void *data, size_t size, size_t count, VFS_FILE *stream)
{
	int r;

	r = fread(data, size, count, (FILE*)(stream->priv));

	return r;
}

static int host_fwrite (const void *data, size_t size, size_t count, VFS_FILE *stream)
{
	int r;

	r = fwrite(data, size, count, (FILE*)(stream->priv));

	return r;
}

static int host_fflush (VFS_FILE *stream)
{
	int r;

	r = fflush((FILE*)(stream->priv));

	return r;
}

static int host_fseek (VFS_FILE *stream, long int offset, int whence)
{
	int r;

	r = fseek((FILE*)(stream->priv), offset, whence);

	return r;
}

static size_t host_ftell (VFS_FILE *stream)
{
	return ftell((FILE*)(stream->priv));
}

static int host_unlink (const char *filename)
{
	int r;

	ASLOG(HOFS, "unlink(%s)\n", filename);

	r = remove(TO_HOFS_PATH(filename));

	return r;
}

static int host_stat (const char *filename, vfs_stat_t *buf)
{
	int r = ENOENT;

	ASLOG(HOFS, "stat(%s)\n", filename);

	if(('\0' == TO_HOFS_PATH(filename)[0])
		|| (0 == strcmp(TO_HOFS_PATH(filename),"/")) )
	{	/* just the root */
		buf->st_mode = S_IFDIR;
		buf->st_size = 0;

		r = 0;
	}
	else
	{
		struct stat st;
		r = stat(TO_HOFS_PATH(filename),&st);
		if(0 == r)
		{
			buf->st_mode = st.st_mode;
			buf->st_size = st.st_size;
		}
	}

	return r;
}

static VFS_DIR * host_opendir (const char *dirname)
{
	VFS_DIR* dir;

	ASLOG(HOFS, "opendir(%s)\n", dirname);

	dir = malloc(sizeof(VFS_DIR));

	if(NULL != dir)
	{
		const char* p;
		dir->fops = &hofs_ops;

		if(('\0' == TO_HOFS_PATH(dirname)[0]))
		{
			p = "./";
		}
		else
		{
			p = TO_HOFS_PATH(dirname);
		}

		dir->priv = (void*)opendir(p);

		if(NULL == dir->priv)
		{
			free(dir);
			dir = NULL;
			ASLOG(HOFS, "opendir failed!\n");
		}
	}

	return dir;

}

static vfs_dirent_t * host_readdir (VFS_DIR *dirstream)
{
	const struct dirent * rentry;
	vfs_dirent_t * rdirent;

	static vfs_dirent_t dirent;

	rentry = readdir((DIR*)(dirstream->priv));

	if(NULL != rentry)
	{
#if defined(__LINUX__)
		dirent.d_namlen = rentry->d_reclen;
#else
		dirent.d_namlen = rentry->d_namlen;
#endif
		strcpy(dirent.d_name, rentry->d_name);

		rdirent = &dirent;

	}
	else
	{
		rdirent = NULL;
	}

	return rdirent;

}

static int host_closedir (VFS_DIR *dirstream)
{
	int r;

	r = closedir((DIR*)(dirstream->priv));

	if (0 == r)
	{
		free(dirstream);
	}

	return r;
}

static int host_chdir (const char *filename)
{

	int r = ENOTDIR;

	ASLOG(HOFS, "chdir(%s)\n", filename);

	if(('\0' == TO_HOFS_PATH(filename)[0]))
	{
		r = 0;
	}
	else
	{
		struct stat st;
		void* faddr = NULL;

		if( (0 == stat(TO_HOFS_PATH(filename), &st)) &&
			(VFS_ISDIR(st.st_mode)) )
		{
			r = 0;
		}
	}

	return r;

}

static int host_mkdir (const char *filename, uint32_t mode)
{
	int r;

	ASLOG(HOFS, "mkdir(%s, 0x%x)\n", filename, mode);

#if defined(__LINUX__)
	r = mkdir(TO_HOFS_PATH(filename), mode);
#else
	r = mkdir(TO_HOFS_PATH(filename));
#endif
	return r;
}

static int host_rmdir (const char *filename)
{
	int r;

	ASLOG(HOFS, "rmdir(%s)\n", filename);

	r = rmdir(TO_HOFS_PATH(filename));

	return r;
}

static int host_rename (const char *oldname, const char *newname)
{
	int r;

	ASLOG(HOFS, "rename (%s, %s)\n", oldname, newname);

	r = rename(TO_HOFS_PATH(oldname), TO_HOFS_PATH(newname));

	return r;
}

/* ============================ [ FUNCTIONS ] ====================================================== */
const struct vfs_filesystem_ops hofs_ops =
{
	.name = "/host",
	.fopen = host_fopen,
	.fclose = host_fclose,
	.fread = host_fread,
	.fwrite = host_fwrite,
	.fflush = host_fflush,
	.fseek = host_fseek,
	.ftell = host_ftell,
	.unlink = host_unlink,
	.stat = host_stat,
	.opendir = host_opendir,
	.readdir = host_readdir,
	.closedir = host_closedir,
	.chdir = host_chdir,
	.mkdir = host_mkdir,
	.rmdir = host_rmdir,
	.rename = host_rename
};
#endif
