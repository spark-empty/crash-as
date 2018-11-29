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
#ifdef USE_PCI
/* ============================ [ INCLUDES  ] ====================================================== */
#ifdef USE_FATFS
#include "diskio.h"
#endif
#include "Std_Types.h"
#include "pci_core.h"
#include "asdebug.h"
#ifdef USE_STDRT
#include "rtthread.h"
#include "rthw.h"
#endif

#ifdef USE_LWEXT4
#include <ext4.h>
#include <ext4_mkfs.h>
#include <ext4_config.h>
#include <ext4_blockdev.h>
#include <ext4_errno.h>
#endif

/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_FATFS 0
#define AS_LOG_EXTFS 1
/* Definitions of physical drive number for each drive */
#define DEV_MMC		0	/* Example: Map MMC/SD card to physical drive 0 : default */
#define DEV_RAM		1	/* Example: Map Ramdisk to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

enum {
	IMG_FATFS = 0,
	IMG_EXT4,
	IMG_BLK2,
	IMG_BLK3,
	IMG_MAX
};
enum{
	REG_BLKID     = 0x00,
	REG_BLKSZ     = 0x04,
	REG_BLKNBR    = 0x08,
	REG_DATA      = 0x0C,
	REG_LENGTH    = 0x10,
	REG_BLKSTATUS = 0x14,
	REG_CMD       = 0x18,
};

#define EXTFS_IMG	"ExtFs.img"
#define EXT4_FILEDEV_BSIZE 4096
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
#ifdef USE_LWEXT4
static int blockdev_open(struct ext4_blockdev *bdev);
static int blockdev_bread(struct ext4_blockdev *bdev, void *buf, uint64_t blk_id,
			 uint32_t blk_cnt);
static int blockdev_bwrite(struct ext4_blockdev *bdev, const void *buf,
			  uint64_t blk_id, uint32_t blk_cnt);
static int blockdev_close(struct ext4_blockdev *bdev);
static int blockdev_lock(struct ext4_blockdev *bdev);
static int blockdev_unlock(struct ext4_blockdev *bdev);
#endif

int PciBlk_Init(uint32_t blkid);
int PciBlk_Read(uint32_t blkid, uint32_t blksz, uint32_t blknbr, uint8_t* data);
int PciBlk_Write(uint32_t blkid, uint32_t blksz, uint32_t blknbr, const uint8_t* data);
int PciBlk_Size(uint32_t blkid, uint32_t *size);
/* ============================ [ DATAS     ] ====================================================== */
static pci_dev *pdev = NULL;
static void* __iobase= NULL;
#ifdef USE_LWEXT4
EXT4_BLOCKDEV_STATIC_INSTANCE(ext4_blkdev, EXT4_FILEDEV_BSIZE, 0, blockdev_open,
			      blockdev_bread, blockdev_bwrite, blockdev_close,
			      blockdev_lock, blockdev_unlock);
#endif

#ifdef RT_USING_DFS
static struct rt_device devF[IMG_MAX];
static struct rt_mutex lock[IMG_MAX];
static struct rt_semaphore sem[IMG_MAX];
#endif /* RT_USING_DFS */
/* ============================ [ LOCALS    ] ====================================================== */
#ifdef USE_LWEXT4
static int blockdev_open(struct ext4_blockdev *bdev)
{
	uint32_t size;

	PciBlk_Init(IMG_EXT4);

	PciBlk_Size(IMG_EXT4, &size);

	bdev->part_offset = 0;
	bdev->part_size = size;
	bdev->bdif->ph_bcnt = bdev->part_size / bdev->bdif->ph_bsize;

	return 0;

}

static int blockdev_bread(struct ext4_blockdev *bdev, void *buf, uint64_t blk_id,
			 uint32_t blk_cnt)
{
	while(blk_cnt > 0)
	{
		PciBlk_Read(IMG_EXT4,bdev->bdif->ph_bsize,blk_id,buf);
		blk_cnt--;
		blk_id ++;
		buf += bdev->bdif->ph_bsize;
	}
	return 0;
}


static int blockdev_bwrite(struct ext4_blockdev *bdev, const void *buf,
			  uint64_t blk_id, uint32_t blk_cnt)
{
	while(blk_cnt > 0)
	{
		PciBlk_Write(IMG_EXT4,bdev->bdif->ph_bsize,blk_id,buf);
		blk_cnt--;
        blk_id++;
		buf += bdev->bdif->ph_bsize;
	}
	return 0;
}

static int blockdev_close(struct ext4_blockdev *bdev)
{
	return 0;
}

static int blockdev_lock(struct ext4_blockdev *bdev)
{
	return 0;
}

static int blockdev_unlock(struct ext4_blockdev *bdev)
{
	return 0;
}

/******************************************************************************/
struct ext4_blockdev *ext4_blockdev_get(void)
{
	return &ext4_blkdev;
}
#endif

#ifdef RT_USING_DFS
static rt_err_t rt_asblk_init_internal(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_asblk_open(rt_device_t dev, rt_uint16_t oflag)
{
    int blkid = (int)dev->user_data;
	PciBlk_Init(blkid);
    return RT_EOK;
}

static rt_err_t rt_asblk_close(rt_device_t dev)
{
    return RT_EOK;
}

/* position: block page address, not bytes address
 * buffer:
 * size  : how many blocks
 */
static rt_size_t rt_asblk_read(rt_device_t dev, rt_off_t position, void *buffer, rt_size_t size)
{
	rt_size_t doSize = size;

    int blkid = (int)dev->user_data;

    rt_mutex_take(&lock[blkid], RT_WAITING_FOREVER);

	while(size > 0)
	{
		PciBlk_Read(blkid,512,position,buffer);
		size--;
        position ++;
		buffer += 512;
	}

	rt_mutex_release(&lock[blkid]);

    return doSize;
}

/* position: block page address, not bytes address
 * buffer:
 * size  : how many blocks
 */
static rt_size_t rt_asblk_write(rt_device_t dev, rt_off_t position, const void *buffer, rt_size_t size)
{

	rt_size_t doSize = size;

    int blkid = (int)dev->user_data;

    rt_mutex_take(&lock[blkid], RT_WAITING_FOREVER);

	while(size > 0)
	{
		PciBlk_Write(blkid,512,position,buffer);
		size--;
        position++;
		buffer += 512;
	}

	rt_mutex_release(&lock[blkid]);

    return doSize;
}

static rt_err_t rt_asblk_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        uint32_t size;
        int blkid = (int)dev->user_data;
        struct rt_device_blk_geometry *geometry;

        PciBlk_Size(blkid, &size);
        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL) return -RT_ERROR;

        geometry->bytes_per_sector = 512;
        geometry->block_size = 512;

        geometry->sector_count = size / 512;
    }

    return RT_EOK;
}
#endif /* RT_USING_DFS */
/* ============================ [ FUNCTIONS ] ====================================================== */
int PciBlk_Init(uint32_t blkid)
{
	imask_t mask;
	if(NULL == __iobase)
	{
		pdev = find_pci_dev_from_id(0xcaac,0x0003);
		if(NULL != pdev)
		{
			__iobase = pci_get_memio(pdev, 1);
			enable_pci_resource(pdev);
		}
	}

	asAssert(__iobase);

	Irq_Save(mask);
	writel(__iobase+REG_BLKID, blkid);
	writel(__iobase+REG_CMD, 0); /* cmd init */
	Irq_Restore(mask);

	return 0;
}

int PciBlk_Read(uint32_t blkid, uint32_t blksz, uint32_t blknbr, uint8_t* data)
{
	uint32_t i;
	imask_t mask;

	asAssert(__iobase);

	Irq_Save(mask);
	writel(__iobase+REG_BLKID, blkid);
	writel(__iobase+REG_BLKSZ, blksz);
	writel(__iobase+REG_BLKNBR, blknbr);
	writel(__iobase+REG_CMD, 1); /* cmd read */
	for(i=0; i < blksz; i++)
	{
		data[i] = readl(__iobase+REG_DATA);
	}
	Irq_Restore(mask);

	return 0;
}

int PciBlk_Write(uint32_t blkid, uint32_t blksz, uint32_t blknbr, const uint8_t* data)
{
	uint32_t i;
	imask_t mask;

	asAssert(__iobase);

	Irq_Save(mask);
	writel(__iobase+REG_BLKID, blkid);
	writel(__iobase+REG_BLKSZ, blksz);
	writel(__iobase+REG_BLKNBR, blknbr);

	for(i=0; i < blksz; i++)
	{
		writel(__iobase+REG_DATA,data[i]);
	}

	writel(__iobase+REG_CMD, 2); /* cmd write */
	Irq_Restore(mask);

	return 0;
}

int PciBlk_Size(uint32_t blkid, uint32_t *size)
{
	imask_t mask;

	asAssert(__iobase);

	Irq_Save(mask);
	writel(__iobase+REG_BLKID, blkid);

	*size = readl(__iobase+REG_LENGTH);
	Irq_Restore(mask);

	return 0;
}
#ifndef USE_STDRT
#ifdef USE_FATFS
DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;

	ASLOG(FATFS,"%s %d\n",__func__,pdrv);

	switch (pdrv) {
	case DEV_RAM :
		break;

	case DEV_MMC :
		stat = RES_OK;
		break;

	case DEV_USB :
		break;
	}
	return stat;
}

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
	ASLOG(FATFS,"%s %d\n",__func__,pdrv);
	switch (pdrv) {
	case DEV_RAM :
		break;

	case DEV_MMC :
	{
		if( 0 == PciBlk_Init(IMG_FATFS))
		{
			stat = 0;
		}
		else
		{
			stat = STA_NODISK;
		}
		break;
	}
	case DEV_USB :
		break;
	}
	return stat;
}

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res = RES_PARERR;
	ASLOG(FATFS,"%s %d %d %d\n",__func__,pdrv,sector,count);
	switch (pdrv) {
	case DEV_RAM :
		break;

	case DEV_MMC :
	{
		res = RES_OK;
		while((RES_OK == res) && (count > 0))
		{
			if(0 != PciBlk_Read(IMG_FATFS,512,sector,buff))
			{
				res = RES_ERROR;
			}
			count --;
			buff += 512;
			sector ++;
		};
		break;
	}

	case DEV_USB :
		break;
	}

	return res;
}

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res = RES_PARERR;
	ASLOG(FATFS,"%s %d %d %d\n",__func__,pdrv,sector,count);
	switch (pdrv) {
	case DEV_RAM :
		break;

	case DEV_MMC :
	{
		res = RES_OK;
		while((RES_OK == res) && (count > 0))
		{
			if(0 != PciBlk_Write(IMG_FATFS,512,sector,buff))
			{
				res = RES_ERROR;
			}
			count --;
			buff += 512;
			sector++;
		};
		break;
	}
	case DEV_USB :
		break;
	}

	return res;
}

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_PARERR;
	ASLOG(FATFS,"%s %d %d\n",__func__,pdrv,cmd);
	switch (pdrv) {
	case DEV_RAM :
		break;

	case DEV_MMC :
	{
		switch (cmd) {
		case CTRL_SYNC:
			res = RES_OK;
			break;

		case GET_SECTOR_COUNT:
		{
			if(0 == PciBlk_Size(IMG_FATFS,buff))
			{
				*(DWORD*)buff = *(DWORD*)buff/512;
				res = RES_OK;
			}
			break;
		}
		case GET_SECTOR_SIZE:
		{
			*(DWORD*)buff = 512;
			res = RES_OK;
			break;
		}
		case GET_BLOCK_SIZE:
			if(0 == PciBlk_Size(IMG_FATFS,buff))
			{
				res = RES_OK;
			}
			break;
		}
		break;
	}
	case DEV_USB :
		break;
	}

	return res;
}

DWORD get_fattime (void)
{
	return 0;
}

#endif /* USE_FATFS */
#endif /* USE_STDRT */

#ifdef USE_LWEXT4
void ext_mount(void)
{
	int rc;

	rc = ext4_device_register(&ext4_blkdev, EXTFS_IMG);
	if(rc != EOK)
	{
		ASLOG(EXTFS, "register ext4 device failed\n");
	}

	rc = ext4_mount(EXTFS_IMG, "/", false);
	if (rc != EOK)
	{
		static struct ext4_fs fs;
		static struct ext4_mkfs_info info = {
			.block_size = EXT4_FILEDEV_BSIZE,
			.journal = true,
		};
		ASWARNING("ExtFs is invalid, do mkfs!\n");
		rc = ext4_mkfs(&fs, &ext4_blkdev, &info, F_SET_EXT4);
		if (rc != EOK)
		{
			printf("ext4_mkfs error: %d\n", rc);
		}
		else
		{
			rc = ext4_mount(EXTFS_IMG, "/", false);
			if (rc != EOK)
			{
				ASLOG(EXTFS, "mount ext4 device failed\n");
			}
		}
	}

	ASLOG(EXTFS, "mount ext4 device " EXTFS_IMG " on / OK\n");
}
#endif

#ifdef RT_USING_DFS
void rt_hw_asblk_init(int blkid)
{
    struct rt_device *device;
    char buffer[16] = "asblk0";

    if( blkid >= IMG_MAX) return;

    rt_mutex_init(&lock[blkid],"fdlock", RT_IPC_FLAG_FIFO);
	rt_sem_init(&sem[blkid], "fdsem", 0, RT_IPC_FLAG_FIFO);

    device = &(devF[blkid]);

    device->type  = RT_Device_Class_Block;
    device->init = rt_asblk_init_internal;
    device->open = rt_asblk_open;
    device->close = rt_asblk_close;
    device->read = rt_asblk_read;
    device->write = rt_asblk_write;
    device->control = rt_asblk_control;
    device->user_data = (void*) blkid;

    buffer[5] = '0' + blkid;
    rt_device_register(device, buffer,
                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE | RT_DEVICE_FLAG_STANDALONE);

}

void rt_hw_asblk_init_all(void)
{
    int i;
    for(i=0; i < IMG_MAX; i++)
    {
        rt_hw_asblk_init(i);
    }
}
#endif /* RT_USING_DFS */

#endif /* USE_PCI */
