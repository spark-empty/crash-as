/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2015  AS <parai@foxmail.com>
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
#ifndef RELEASE_ASCORE_VIRTUAL_AS_VIRTUAL_INCLUDE_VIRTIO_H_
#define RELEASE_ASCORE_VIRTUAL_AS_VIRTUAL_INCLUDE_VIRTIO_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdint.h>
#include <stdbool.h>
#include <QThread>
#include <QDebug>
#ifdef __WINDOWS__
#include <windows.h>
#else
#include <pthread.h>
#include <dlfcn.h>
#endif
#include <QList>
#include <assert.h>
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#define IPC_FIFO_SIZE 1024

#define RPMSG_NAME_SERVICE_PORT 53

#define RPROC_RSC_NUM  1
#define RPROC_RPMSG_CFG_SIZE  16
#define RPROC_NUM_OF_VRINGS 2

#define RPROC_RPMSG_FEATURES (1 << 0)

/* This marks a buffer as continuing via the next field. */
#define VRING_DESC_F_NEXT	1
/* This marks a buffer as write-only (otherwise read-only). */
#define VRING_DESC_F_WRITE	2
/* This means the buffer contains a list of buffer descriptors. */
#define VRING_DESC_F_INDIRECT	4

/* The Host uses this in used->flags to advise the Guest: don't kick me when
 * you add a buffer.  It's unreliable, so it's simply an optimization.  Guest
 * will still kick if it's out of buffers. */
#define VRING_USED_F_NO_NOTIFY	1
/* The Guest uses this in avail->flags to advise the Host: don't interrupt me
 * when you consume a buffer.  It's unreliable, so it's simply an
 * optimization.  */
#define VRING_AVAIL_F_NO_INTERRUPT	1

/* We support indirect buffer descriptors */
#define VIRTIO_RING_F_INDIRECT_DESC	28

/* The Guest publishes the used index for which it expects an interrupt
 * at the end of the avail ring. Host should ignore the avail->flags field. */
/* The Host publishes the avail index for which it expects a kick
 * at the end of the used ring. Guest should ignore the used->flags field. */
#define VIRTIO_RING_F_EVENT_IDX		29

/* Alignment requirements for vring elements.
 * When using pre-virtio 1.0 layout, these fall out naturally.
 */
#define VRING_AVAIL_ALIGN_SIZE 2
#define VRING_USED_ALIGN_SIZE 4
#define VRING_DESC_ALIGN_SIZE 16

#define RPMSG_NAME_SIZE			32
#define RPMSG_DATA_SIZE         512

extern unsigned long Ipc_BaseAddress;
#define IPC_MAP_PA_TO_VA(addr) ((void*)(unsigned long)(Ipc_BaseAddress+addr))
/* ============================ [ TYPES     ] ====================================================== */
/* Virtio ring descriptors: 16 bytes.  These can chain together via "next". */
typedef struct {
    /* Address (guest-physical). */
    quint32 addr;
    /* Length. */
    quint32 len;
    /* The flags as indicated above. */
    quint16 flags;
    /* We chain unused descriptors via this, too */
    quint16 next;
}Vring_DescType;

typedef struct {
    quint16 flags;
    quint16 idx;
    quint16 ring[];
}Vring_AvailType;

/* u32 is used here for ids for padding reasons. */
typedef struct {
    /* Index of start of used descriptor chain. */
    quint32 id;
    /* Total length of the descriptor chain which was used (written to) */
    quint32 len;
}Vring_UsedElemType;

typedef struct {
    quint16 flags;
    quint16 idx;
    Vring_UsedElemType ring[];
}Vring_UsedType;

typedef struct {
    quint32 num;	/* must be 2^n */

    Vring_DescType *desc;

    Vring_AvailType *avail;

    Vring_UsedType *used;
}Vring_Type;

typedef quint8 Ipc_ChannelType;
typedef quint32 VirtQ_IdxType;
typedef quint32 VirtQ_IdxSizeType;
typedef struct
{
    VirtQ_IdxSizeType count;
    VirtQ_IdxType     idx[IPC_FIFO_SIZE];
}Ipc_FifoType;

typedef enum {
    RSC_CARVEOUT	= 0,
    RSC_DEVMEM	= 1,
    RSC_TRACE	= 2,
    RSC_VDEV	= 3,
    RSC_LAST	= 4,
}Rproc_ReourceType;

typedef struct {
    /* For 64 bit ECU, address is 64 bit */
    quint32 da;
    quint32 align;
    quint32 num;
    quint32 notifyid;
    quint32 reserved;
}Rproc_ReseouceVdevVringType;

typedef struct {
    quint32 type;
    quint32 id;
    quint32 notifyid;
    quint32 dfeatures;
    quint32 gfeatures;
    quint32 config_len;
    quint8 status;
    quint8 num_of_vrings;
    quint8 reserved[2];
    Rproc_ReseouceVdevVringType vring[RPROC_NUM_OF_VRINGS];
}Rproc_ResourceVdevType;

typedef struct
{
    quint32 version;
    quint32 num;
    quint32 reserved[2];
    quint32 offset[RPROC_RSC_NUM];  /* Should match 'num' in actual definition */
    Rproc_ResourceVdevType rpmsg_vdev;
#if RPROC_RPMSG_CFG_SIZE > 0 /* @config_len of Rproc_ResourceVdevType */
    quint8                 rpmsg_cfg[RPROC_RPMSG_CFG_SIZE];
#endif
}Rproc_ResourceTableType;

typedef struct{
    quint32 src;
    quint32 dst;
    quint32 reserved;
    quint16 len;
    quint16 flags;
    quint8 data[RPMSG_DATA_SIZE];
} RPmsg_HandlerType;

typedef struct rpmsg_ns_msg {
    char name[RPMSG_NAME_SIZE];
    quint32 addr;
    quint32 flags;
} RPmsg_NamseServiceMessageType;

typedef enum{
    RPMSG_NS_CREATE		= 0,
    RPMSG_NS_DESTROY	= 1,
} RPmsg_NameServiceFlagType;

typedef struct {
    // the CAN ID, 29 or 11-bit
    quint32 	id;
    quint8     bus;
    // Length, max 8 bytes
    quint8		length;
    // data ptr
    quint8 		sdu[8];
} Can_RPmsgPduType;

typedef bool (*PF_IPC_IS_READY)(Ipc_ChannelType chl);
extern void Virtio_SetIpcBaseAddress(unsigned long base);
/* ============================ [ CLASS     ] ====================================================== */
class Vring{
private:
    Rproc_ReseouceVdevVringType* ring;
    Vring_Type vr;
    /* Last available index */
    VirtQ_IdxType           last_avail_idx;

    /* Last available index */
    VirtQ_IdxType           last_used_idx;

    /* Head of free buffer list. */
    quint32 free_head;
    /* Number we've added since last sync. */
    quint32 num_added;
    quint32 heap[1024*1024/4];
public:
    explicit Vring ( Rproc_ReseouceVdevVringType* ring ) : ring(ring)
    {
        init();
    }
    quint32 ring_num(void){ return vr.num; }
    VirtQ_IdxType get_notifyid(void)
    {
        return ring->notifyid;
    }
    void* get_used_buf(VirtQ_IdxType* idx,quint32 *len)
    {
        void* buf;
        Vring_UsedElemType* used;
        /* There's nothing available? */
        if (last_used_idx == vr.used->idx) {
            /* We need to know about added buffers */
            vr.avail->flags &= ~VRING_AVAIL_F_NO_INTERRUPT;

            buf = NULL;
        }
        else
        {
            /*
             * Grab the next descriptor number they're advertising, and increment
             * the index we've seen.
             */
            used = &(vr.used->ring[last_used_idx++ % vr.num]);
            *idx = used->id;
            *len = used->len;
            buf = IPC_MAP_PA_TO_VA(vr.desc[*idx].addr);

            num_added--;
        }

        return buf;
    }
    void put_used_buf_back(VirtQ_IdxType idx)
    {
       ASLOG(OFF,"put_used_buf_back(idx=%d),vr.avail->idx=%d\n",idx,vr.avail->idx);
       if (idx > vr.num) {
           assert(0);
       }
       else
       {
           vr.avail->ring[vr.avail->idx++ % vr.num] = idx;
           num_added ++;
       }
    }
    bool add_buf(void* data, quint32 len)
    {
        bool added;
        if(num_added<vr.num)
        {
            if(8 == sizeof(void*))
            {
                Virtio_SetIpcBaseAddress(((unsigned long)data)&0xFFFFFFFF00000000UL);
            }
            vr.desc[free_head].addr = (quint32)(unsigned long) data;
            vr.desc[free_head].len  = len;
            vr.desc[free_head].flags = VRING_DESC_F_NEXT;
            free_head = vr.desc[free_head].next;
            vr.avail->idx ++;
            vr.avail->ring[free_head] = free_head;
            num_added ++;
            added = true;
            ASLOG(VRING,"add_buf(%X) vr.avail->idx=%d\n",(int)(unsigned long)data,vr.avail->idx);
        }
        else
        {
            added = false;
        }
        return added;
    }

private:
    void init(void)
    {
        void *p = malloc(size());
        memset(p,0,size());
        ring->da = (quint32)(unsigned long)p;
        vr.num = ring->num;
        vr.desc = (Vring_DescType*)p;
        vr.avail = (Vring_AvailType*)((unsigned long)p + ring->num*sizeof(Vring_DescType));
        vr.used = (Vring_UsedType*)(((unsigned long)(&vr.avail->ring[ring->num]) + sizeof(quint16)
            + ring->align-1) & ~((unsigned long)ring->align - 1));
        for(quint32 i=0;i<(vr.num-1);i++)
        {
            vr.desc[i].next = i+1;
        }

        free_head = 0;
        num_added = 0;

        last_avail_idx = 0;
        last_used_idx  = 0;

        if(8 == sizeof(void*))
        {
            Virtio_SetIpcBaseAddress(((unsigned long)p)&0xFFFFFFFF00000000UL);
        }
        ASLOG(OFF,"vring[idx=%Xh,size=%d]: num=%d, desc=%s, avail=%s, used=%s, da=%Xh\n",
                ring->notifyid,
                size(),vr.num,ASHEX(vr.desc),
                ASHEX(vr.avail),ASHEX(vr.used),ring->da);
    }
    quint32 size(void)
    {
        /*
         * ((12*256+2*(3+256)+4096-1)&~(4096-1))+2*3+8*256 = 6150
         */
        ASLOG(OFF,"sizeof(Vring_DescType)=%d,sizeof(Vring_UsedElemType)=%d,sizeof(quint16)=%d,num=%d,align=%d\n",
              sizeof(Vring_DescType),sizeof(Vring_UsedElemType),sizeof(quint16),ring->num,ring->align);
        return ((sizeof(Vring_DescType) * ring->num + sizeof(quint16) * (3 + ring->num)
             + ring->align - 1) & ~(ring->align - 1))
            + sizeof(quint16) * 3 + sizeof(Vring_UsedElemType) * ring->num;
    }
};
class Vdev: public QObject
{
Q_OBJECT
private:
    Rproc_ResourceVdevType* vdev;
    Vring* r_ring;
    Vring* w_ring;
public:
    explicit Vdev ( Rproc_ResourceVdevType* vdev ): vdev(vdev)
    {
        r_ring = new Vring(&vdev->vring[1]);
        w_ring = new Vring(&vdev->vring[0]);
    }
    void start(void)
    {
        kick_w();
    }
    void kick_w(void)
    {
        emit kick(w_ring->get_notifyid());
    }

    void kick_r(void)
    {
        emit kick(r_ring->get_notifyid());
    }

    bool notify(VirtQ_IdxType idx)
    {
          bool notifed = true;
          if(idx==r_ring->get_notifyid())
          {
              rx_noificaton();
          }
          else if(idx==w_ring->get_notifyid())
          {
              tx_confirmation();
          }
          else
          {
              notifed = false;
          }
          return notifed;
    }
public:
    quint32 r_ring_num(void) {return r_ring->ring_num();}
    quint32 w_ring_num(void) {return w_ring->ring_num();}
    bool provide_a_r_buffer(void* data,quint32 len)
    {   /* thus the remote proc can send a messsage via this buffer */
        return r_ring->add_buf(data,len);
    }
    void* get_used_r_buf(VirtQ_IdxType* idx,quint32 *len)
    {
        return r_ring->get_used_buf(idx,len);
    }
    void put_used_r_buf_back(VirtQ_IdxType idx)
    {
        r_ring->put_used_buf_back(idx);
    }
    VirtQ_IdxType get_r_notifyid(void)
    {
        return r_ring->get_notifyid();
    }

    bool provide_a_w_buffer(void* data,quint32 len)
    {  /* thus a message in data was transimited to the retome proc */
        return w_ring->add_buf(data,len);
    }
    void* get_used_w_buf(VirtQ_IdxType* idx,quint32 *len)
    {
        return w_ring->get_used_buf(idx,len);
    }
    void put_used_w_buf_back(VirtQ_IdxType idx)
    {
        w_ring->put_used_buf_back(idx);
    }
    VirtQ_IdxType get_w_notifyid(void)
    {
        return w_ring->get_notifyid();
    }

public: 
    virtual void rx_noificaton(void){
        VirtQ_IdxSizeType idx;
        quint32 len;
        void* buf;
        ASLOG(VDEV,"rx_notification(idx=%Xh)\n",r_ring->get_notifyid());
        buf = r_ring->get_used_buf(&idx,&len);

        assert(buf);
        ASLOG(VDEV,"Message(idx=%d,len=%d)\n",idx,len);
        asmem(buf,len);

        r_ring->put_used_buf_back(idx);

    }
    virtual void tx_confirmation(void){
        ASLOG(VDEV,"tx_confirmation(idx=%Xh)\n",w_ring->get_notifyid());
    }
    virtual void Can_Write(quint8 busid,quint32 canid,quint8 dlc,quint8* data){
        (void)busid;(void)canid;(void)dlc;(void)busid;(void)data;
    }
    virtual void Shell_Write(QString cmd){ (void)cmd;}

signals:
    void kick(unsigned int idx);
};

class RPmsg: public Vdev
{
Q_OBJECT
private:
    QList<void*> w_buffer;
    quint32 sample_src_ept;
    quint32 sample_can_ept;
    quint32 sample_shell_ept;
    bool    online;
public:
    explicit RPmsg ( Rproc_ResourceVdevType* rpmsg );
    void Can_Write(quint8 busid,quint32 canid,quint8 dlc,quint8* data);
    void Shell_Write(QString cmd);
private slots:

public:
    void rx_noificaton(void);
    void tx_confirmation(void);
signals:
    void Can_RxIndication(quint8,quint32,quint8,quint8*);
};

class Virtio: public QThread
{
Q_OBJECT
private:
    void* hxDll;

    size_t sz_fifo;
    void*  r_lock;
    void*  w_lock;
    void*  r_event;
    void*  w_event;

    Ipc_ChannelType chl;

    Ipc_FifoType* r_fifo;
    Ipc_FifoType* w_fifo;
    quint32 r_pos;
    quint32 w_pos;

    PF_IPC_IS_READY pfIsIpcReady;

    Rproc_ResourceTableType* rsc_tbl;

    QList<Vdev*> vdev_list;

#ifdef __LINUX__
    pthread_mutex_t w_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t r_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t  w_cond  = PTHREAD_COND_INITIALIZER;
    pthread_cond_t  r_cond  = PTHREAD_COND_INITIALIZER;
#endif

public:
    explicit Virtio ( void* dll, QObject *parent = 0);
    ~Virtio ( );
    void Can_Write(quint8 busid,quint32 canid,quint8 dlc,quint8* data);
    void Shell_Write(QString cmd);
private slots:
    void On_Can_RxIndication(quint8 busid,quint32 canid,quint8 dlc,quint8* data);
private:
    void run(void);
    bool fifo_read(VirtQ_IdxType* id);
    bool fifo_write(VirtQ_IdxType id);
signals:
    void Can_RxIndication(quint8 busid,quint32 canid,quint8 dlc,quint8* data);
protected:

private slots:
    void kick(unsigned int idx);
};

/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#endif /* RELEASE_ASCORE_VIRTUAL_AS_VIRTUAL_INCLUDE_VIRTIO_H_ */
