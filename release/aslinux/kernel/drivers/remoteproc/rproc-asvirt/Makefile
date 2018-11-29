#/**
# * AS - the open source Automotive Software on https://github.com/parai
# *
# * Copyright (C) 2015  AS <parai@foxmail.com>
# *
# * This source code is free software; you can redistribute it and/or modify it
# * under the terms of the GNU General Public License version 2 as published by the
# * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
# *
# * This program is distributed in the hope that it will be useful, but
# * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# * for more details.
# */

prj-dir = $(subst /release/aslinux/kernel/drivers/remoteproc/rproc-asvirt,,$(CURDIR))

INFRASTRUCTURE = $(prj-dir)/com/as.infrastructure
APPLICATION = $(prj-dir)/com/as.application
PY34 = python3
LNFS  = $(PY34) $(prj-dir)/release/make/lnfs.py

dep:
	@($(LNFS) $(INFRASTRUCTURE)/include FALSE)
	@($(LNFS) $(INFRASTRUCTURE)/communication/RPmsg FALSE)
	@($(LNFS) $(INFRASTRUCTURE)/arch/posix/mcal/Ipc.h Ipc.h)
	@($(LNFS) $(INFRASTRUCTURE)/arch/posix/mcal/Ipc.c Ipc.c)
	@($(LNFS) $(APPLICATION)/common/config/RPmsg_Cfg.h RPmsg_Cfg.h)
	@($(LNFS) $(APPLICATION)/common/config/RPmsg_Cfg.c RPmsg_Cfg.c)
	@($(LNFS) $(APPLICATION)/common/config/Rproc_Cfg.h Rproc_Cfg.h)
	@($(LNFS) $(APPLICATION)/common/config/Rproc_Cfg.c Rproc_Cfg.c)
	@($(LNFS) $(APPLICATION)/common/config/VirtQ_Cfg.h VirtQ_Cfg.h)
	@($(LNFS) $(APPLICATION)/common/config/VirtQ_Cfg.c VirtQ_Cfg.c)
	@($(LNFS) $(APPLICATION)/board.posix/common/Ipc_Cfg.h Ipc_Cfg.h)
	@($(LNFS) $(APPLICATION)/board.posix/common/Ipc_Cfg.c Ipc_Cfg.c)


obj-y += RPmsg.o RPmsg_Cfg.o Rproc_Cfg.o VirtQ.o VirtQ_Cfg.o Ipc_Cfg.o Ipc.o

CFLAGS += -DUSE_LINUX
