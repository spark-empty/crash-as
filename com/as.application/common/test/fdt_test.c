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

#if defined(USE_SHELL) //&& defined(USE_VFS) && defined(USE_FDT)
#include "shell.h"
#include "libfdt.h"
#include "asdebug.h"
#include "vfs.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
static int shellLibfdt(int argc, char *argv[]);
/* ============================ [ DATAS     ] ====================================================== */
SHELL_CONST ShellCmdT cmdLibfdt  = {
		shellLibfdt,
		1,1,
		"fdt",
		"fdt dtb",
		"fdt sample test to dump dtb",
		{NULL,NULL}
};
SHELL_CMD_EXPORT(cmdLibfdt)
/* ============================ [ LOCALS    ] ====================================================== */
static int shellLibfdt(int argc, char *argv[])
{
	const char* dtb = argv[1];

	VFS_FILE* fp;
	vfs_stat_t st;
	void* faddr = NULL;
	int r;
	int node,property;
	const struct fdt_property *prop;

	if( (0==vfs_stat(dtb, &st)) &&
		(VFS_ISREG(st.st_mode)) )
	{
		fp = vfs_fopen(dtb, "rb");

		if(NULL != fp)
		{
			faddr = malloc(st.st_size);
			if(NULL != faddr)
			{
				vfs_fread(faddr, st.st_size, 1, fp);
			}
			vfs_fclose(fp);
		}
	}

	if(NULL != faddr)
	{

		r = fdt_check_header(faddr);
		if(r != 0)
		{
			SHELL_printf("invalid header\n");
		}
		else
		{
			fdt_for_each_property_offset(property, faddr, 0)
			{
				prop = fdt_get_property_by_offset(faddr, property, NULL);
				SHELL_printf("property: %s = %s(%d)\n",
						fdt_get_string(faddr, fdt32_ld(&prop->nameoff), NULL),
						prop->data, fdt32_ld((const fdt32_t *)(prop->data)));
			}
			fdt_for_each_subnode(node, faddr, 0)
			{
				SHELL_printf("node %d : %s\n", node, fdt_get_name(faddr, node, NULL));
				fdt_for_each_property_offset(property, faddr, node)
				{
					prop = fdt_get_property_by_offset(faddr, property, NULL);
					SHELL_printf("  property: %s = %s(%d)\n",
							fdt_get_string(faddr, fdt32_ld(&prop->nameoff), NULL),
							prop->data, fdt32_ld((const fdt32_t *)(prop->data)));
				}
			}
		}
		free(faddr);
	}

	return 0;
}
/* ============================ [ FUNCTIONS ] ====================================================== */

void fdt_test_init(void)
{
#if !defined(USE_SHELL_SYMTAB)
	SHELL_AddCmd(&cmdLibfdt);
#endif
}

#endif
