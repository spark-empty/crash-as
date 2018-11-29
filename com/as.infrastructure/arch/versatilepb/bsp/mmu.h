#ifndef __MMU_H
#define __MMU_H

#include "mm.h"

/* assembly level */
uint32_t __mmu_getttbl();
uint32_t __mmu_getfsr();
uint32_t __mmu_getfar();
void __mmu_setttbl(void *base);
uint32_t __mmu_getdomain();
void __mmu_setdomain(uint32_t value);
uint32_t __mmu_getcr();
void __mmu_setcr(uint32_t value);

/* domain type */
#define DOMAIN_NOACESS	0x00
#define DOMAIN_CLIENT	0x01
#define DOMAIN_MANAGER	0x03
/* mmu control register */
#define MMU_CR_ENABLE		0x0000001
#define MMU_CR_ALIGN_FAULT	0x0000002
#define MMU_CR_DCACHE		0x0000004
#define MMU_CR_SYS_PROT		0x0000100
#define MMU_CR_ROM_PROT		0x0000200

void domain_set_protection(int present);
int domain_setup(uint32_t num, uint32_t flags);
int page_dir_set(struct pgdir_t *dir);
void mmu_enable();
void mmu_disable();


#endif
