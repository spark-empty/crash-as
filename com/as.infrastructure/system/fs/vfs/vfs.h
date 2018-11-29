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
#ifndef _VFS_H
#define _VFS_H

/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/stat.h>
#if defined(__WINDOWS__) || defined(__LINUX__)
#else
#include <sys/dirent.h>
#endif
#include <time.h>
#include <errno.h>
/* ============================ [ MACROS    ] ====================================================== */
#ifndef S_IRWXG
#define S_IRWXG              00070
#endif
#ifndef S_IRWXO
#define S_IRWXO              00007
#endif
#ifndef S_ISDIR
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif
#ifndef S_ISREG
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif
#define VFS_ISDIR(st_mode) S_ISDIR(st_mode)
#define VFS_ISREG(st_mode) S_ISREG(st_mode)
/* ============================ [ TYPES     ] ====================================================== */

struct vfs_filesystem_ops fops;

typedef struct
{
	const struct vfs_filesystem_ops* fops;
	void* priv;
} VFS_DIR;

typedef struct
{
	const struct vfs_filesystem_ops* fops;
	void* priv;
} VFS_FILE;

#ifdef USE_LIBELF
typedef struct stat vfs_stat_t;
typedef struct dirent vfs_dirent_t;
#else
typedef struct {
	uint32_t st_mode;     /* File mode */
	size_t   st_size;     /* File size (regular files only) */
} vfs_stat_t;

typedef struct
{
	unsigned short	d_namlen;	/* Length of name in d_name. */
	char		d_name[FILENAME_MAX]; /* [FILENAME_MAX] */ /* File name. */
} vfs_dirent_t;
#endif

/* File system operations */
struct vfs_filesystem_ops
{
    const char *name;

    /* operations for file */
    VFS_FILE* (*fopen) (const char *filename, const char *opentype);
    int (*fclose) (VFS_FILE* stream);
    int (*fread) (void *data, size_t size, size_t count, VFS_FILE *stream);
    int (*fwrite) (const void *data, size_t size, size_t count, VFS_FILE *stream);
    int (*fflush) (VFS_FILE *stream);
    int (*fseek) (VFS_FILE *stream, long int offset, int whence);
	size_t (*ftell)  (VFS_FILE *stream);

    int (*unlink) (const char *filename);
    int (*stat) (const char *filename, vfs_stat_t *buf);

    VFS_DIR * (*opendir) (const char *dirname);
    vfs_dirent_t * (*readdir) (VFS_DIR *dirstream);
    int (*closedir) (VFS_DIR *dirstream);

    int (*chdir) (const char *filename);
    int (*mkdir) (const char *filename, uint32_t mode);
    int (*rmdir) (const char *filename);
    int (*rename) (const char *oldname, const char *newname);
};
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
VFS_FILE* vfs_fopen (const char *filename, const char *opentype);
int vfs_fclose (VFS_FILE* stream);
int vfs_fread (void *data, size_t size, size_t count, VFS_FILE *stream);
int vfs_fwrite (const void *data, size_t size, size_t count, VFS_FILE *stream);
int vfs_fflush (VFS_FILE *stream);
int vfs_fseek (VFS_FILE *stream, long int offset, int whence);
size_t vfs_ftell (VFS_FILE *stream);

int vfs_unlink (const char *filename);
int vfs_stat (const char *filename, vfs_stat_t *buf);

VFS_DIR * vfs_opendir (const char *dirname);
vfs_dirent_t * vfs_readdir (VFS_DIR *dirstream);
int vfs_closedir (VFS_DIR *dirstream);

int vfs_chdir (const char *filename);
char * vfs_getcwd  (char *buffer, size_t size);
int vfs_mkdir (const char *filename, uint32_t mode);
int vfs_rmdir (const char *filename);
int vfs_rename (const char *oldname, const char *newname);

char* vfs_find(const char* file);

int vfs_fprintf (VFS_FILE* fp, const char* fmt, ...);
#endif /* _VFS_H */
