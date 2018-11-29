/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
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
#ifdef USE_FATFS
/* ============================ [ INCLUDES  ] ====================================================== */
#ifdef _WIN32
#undef _WIN32
#endif
#include "ff.h"
#ifdef __WINDOWS__
#define _WIN32
#endif
#ifdef USE_STDRT
#define HAVE_DIR_STRUCTURE
#if _FS_RPATH == 0
#error macro _FS_RPATH is 0, please modify it to 1 or 2 in file "rt-thread/components/dfs/filesystems/elmfat/ffconf.h"
#endif
#define f_rmdir f_unlink
#endif
#include "vfs.h"
#include <string.h>
#include <stdlib.h>
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_FATFS 0
#define TO_FATFS_PATH(f) (&((f)[5]))
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
extern const struct vfs_filesystem_ops fatfs_ops;
/* ============================ [ DATAS     ] ====================================================== */
/* dirent that will be given to callers;
 * note: both APIs assume that only one dirent ever exists
 */
static vfs_dirent_t dir_ent;
/* ============================ [ LOCALS    ] ====================================================== */
static VFS_FILE* fatfs_fopen (const char *filename, const char *opentype)
{
	VFS_FILE *f;
	BYTE flags = 0;
	FRESULT r;

	ASLOG(FATFS, "fopen(%s,%s)\n", filename, opentype);

	f = malloc(sizeof(VFS_FILE));
	if(NULL == f)
	{
		return NULL;
	}

	f->priv = malloc(sizeof(FIL));
	if(NULL == f->priv)
	{
		free(f);
		return NULL;
	}

	while (*opentype != '\0')
	{
		if (*opentype == 'r')
		{
			flags |= FA_READ;
		}
		else if (*opentype == 'w')
		{
			flags |= FA_WRITE | FA_CREATE_ALWAYS;
		}
		else if (*opentype == 'a')
		{
			flags |= FA_OPEN_APPEND;
		}
		else if (*opentype == '+')
		{
			flags |= FA_WRITE;
		}
		opentype++;
	}

	r = f_open(f->priv, TO_FATFS_PATH(filename), flags);
	if (FR_OK != r)
	{
		free(f->priv);
		free(f);
		return NULL;
	}
	else
	{
		f->fops = &fatfs_ops;
	}

	return f;
}

static int fatfs_fclose(VFS_FILE* stream)
{
	FRESULT r;

	r = f_close(stream->priv);
	if (FR_OK != r)
	{
		ASLOG(FATFS, "fclose failed!(%d)\n", r);
		return EOF;
	}

	free(stream->priv);
	free(stream);

	return 0;
}

static int fatfs_fread (void *data, size_t size, size_t count, VFS_FILE *stream)
{
	UINT bytesread;
	FRESULT r;

	ASLOG(FATFS, "fread(%p,%d,%d,%p)\n", data, size, count, stream);

	r = f_read(stream->priv, data, size*count, &bytesread);
	if (FR_OK != r)
	{
		ASLOG(FATFS, "fread failed!(%d)\n", r);
		return 0;
	}

	return (bytesread/size);
}

static int fatfs_fwrite (const void *data, size_t size, size_t count, VFS_FILE *stream)
{
	UINT byteswritten;
	FRESULT r;

	ASLOG(FATFS, "fwrite(%p,%d,%d,%p)\n", data, size, count, stream);

	r = f_write(stream->priv, data, size*count, &byteswritten);
	if (FR_OK != r)
	{
		ASLOG(FATFS, "fwrite failed!(%d)\n", r);
		return 0;
	}

	return (byteswritten/size);
}

static int fatfs_fflush (VFS_FILE *stream)
{
	FRESULT r;

	r = f_sync(stream->priv);
	if (FR_OK == r)
	{
		return 0;
	}

	return EOF;
}

static int fatfs_fseek (VFS_FILE *stream, long int offset, int whence)
{
	FRESULT r;

	if(SEEK_SET != whence) return EOF;

	r = f_lseek(stream->priv, offset);
	if (FR_OK == r)
	{
		return 0;
	}

	ASLOG(FATFS, "fseek failed!(%d)\n", r);

	return EOF;
}

static size_t fatfs_ftell (VFS_FILE *stream)
{
	return ((FIL*)(stream->priv))->fptr;
}

static int fatfs_unlink (const char *filename)
{
	FRESULT r;

	ASLOG(FATFS, "unlink(%s)\n", filename);

	r = f_unlink(TO_FATFS_PATH(filename));
	if (FR_OK == r)
	{
		return 0;
	}

	return EOF;
}

static int fatfs_stat (const char *filename, vfs_stat_t *buf)
{
	FILINFO f;
	FRESULT r;

	ASLOG(FATFS, "stat(%s)\n", filename);

	if(('\0' == TO_FATFS_PATH(filename)[0])
		|| (0 == strcmp(TO_FATFS_PATH(filename),"/")) )
	{	/* just the root */
		f.fsize = 0;
		f.fattrib = AM_DIR;
	}
	else
	{
		r = f_stat(TO_FATFS_PATH(filename), &f);

		if (FR_OK != r)
		{
			ASLOG(FATFS, "stat failed!(%d)\n", r);
			return ENOENT;
		}
	}

	buf->st_size = f.fsize;

	buf->st_mode = 0;

	if(f.fattrib&AM_DIR)
	{
		buf->st_mode |= S_IFDIR;
	}
	else
	{
		buf->st_mode |= S_IFREG;
	}

	if(f.fattrib&AM_RDO)
	{
		buf->st_mode |= S_IEXEC|S_IREAD;
	}
	else
	{
		buf->st_mode |= S_IEXEC|S_IREAD|S_IWRITE;
	}

	return 0;
}

static VFS_DIR * fatfs_opendir (const char *dirname)
{
	VFS_DIR* dir;
	FRESULT r;

	ASLOG(FATFS, "opendir(%s)\n", dirname);

	dir = malloc(sizeof(VFS_DIR));

	if(NULL == dir)
	{
		return NULL;
	}

	dir->priv = malloc(sizeof(DIR));
	if(NULL == dir->priv)
	{
		free(dir);
		return NULL;
	}

	r = f_opendir(dir->priv, TO_FATFS_PATH(dirname));
	if (FR_OK != r)
	{
		ASLOG(FATFS, "opendir(%s) failed!(%d)\n", dirname, r);
		free(dir->priv);
		free(dir);
		return NULL;
	}
	else
	{
		dir->fops = &fatfs_ops;
	}

	return dir;
}
static vfs_dirent_t* fatfs_readdir(VFS_DIR* dir)
{
	FILINFO fi;
	FRESULT r;

	r = f_readdir(dir->priv, &fi);

	if (FR_OK != r)
	{
		return NULL;
	}

	if (0 == fi.fname[0])
	{
		return NULL;
	}

	dir_ent.d_namlen = strnlen(fi.fname,sizeof(fi.fname));

	strcpy(dir_ent.d_name, fi.fname);

	return &dir_ent;
}

static int fatfs_closedir(VFS_DIR* dir)
{
	FRESULT r;

	r = f_closedir(dir->priv);

	if (FR_OK == r)
	{
		free(dir->priv);
		free(dir);
		return 0;
	}

	return EBADF;
}

static int fatfs_chdir (const char *filename)
{
	FRESULT r;

	ASLOG(FATFS, "chdir(%s)\n", filename);
	if(('\0' == TO_FATFS_PATH(filename)[0]))
	{
		r = f_chdir("/");
	}
	else
	{
		r = f_chdir(TO_FATFS_PATH(filename));
	}

	if (FR_OK == r)
	{
		return 0;
	}

	ASLOG(FATFS, "chdir(%s) failed!(%d)\n", filename, r);

	return ENOTDIR;
}

static int fatfs_mkdir (const char *filename, uint32_t mode)
{
	FRESULT r;

	ASLOG(FATFS, "mkdir(%s, 0x%x)\n", filename, mode);

	r = f_mkdir(TO_FATFS_PATH(filename));

	if (FR_OK == r)
	{
		return 0;
	}

	ASLOG(FATFS, "mkdir failed!(%d)\n", r);
	if ( FR_EXIST == r )
	{
		return EEXIST;
	}

	return EACCES;
}

static int fatfs_rmdir (const char *filename)
{
	FRESULT r;

	ASLOG(FATFS, "rmdir(%s)\n", filename);

	r = f_rmdir(TO_FATFS_PATH(filename));

	if (FR_OK == r)
	{
		return 0;
	}

	return EACCES;
}

static int fatfs_rename (const char *oldname, const char *newname)
{
	FRESULT r;

	ASLOG(FATFS, "rename(%s,%s)\n", oldname, newname);

	r = f_rename(TO_FATFS_PATH(oldname),TO_FATFS_PATH(newname));

	if (FR_OK == r)
	{
		return 0;
	}

	return EACCES;
}

/* ============================ [ FUNCTIONS ] ====================================================== */
const struct vfs_filesystem_ops fatfs_ops =
{
	.name = "/vfat",
	.fopen = fatfs_fopen,
	.fclose = fatfs_fclose,
	.fread = fatfs_fread,
	.fwrite = fatfs_fwrite,
	.fflush = fatfs_fflush,
	.fseek = fatfs_fseek,
	.ftell = fatfs_ftell,
	.unlink = fatfs_unlink,
	.stat = fatfs_stat,
	.opendir = fatfs_opendir,
	.readdir = fatfs_readdir,
	.closedir = fatfs_closedir,
	.chdir = fatfs_chdir,
	.mkdir = fatfs_mkdir,
	.rmdir = fatfs_rmdir,
	.rename = fatfs_rename
};
#endif
