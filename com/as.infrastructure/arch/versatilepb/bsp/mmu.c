/* MMU stuff
 * Marcos Medeiros
 */
#ifdef USE_MMU_C
#include "Std_Types.h"
#include "mmu.h"

void domain_set_protection(int present)
{
	uint32_t cr = __mmu_getcr();
	if (present)
		cr |= MMU_CR_SYS_PROT;
	else
		cr &= ~MMU_CR_SYS_PROT;
	__mmu_setcr(cr);
}

int domain_setup(uint32_t num, uint32_t flags)
{
	if (num >= 16) {
		return -1;
	}

	uint32_t dom = __mmu_getdomain();
	dom = ((flags & 3) << (num << 1));
	__mmu_setdomain(dom);
	return -0;
}

int page_dir_set(struct pgdir_t *dir)
{
	if (!dir) {
		return -1;
	}
	__mmu_setttbl(dir);
	return 0;
}

void mmu_enable()
{
	uint32_t cr = __mmu_getcr();
	cr |= MMU_CR_ENABLE;
	__mmu_setcr(cr);
}

void mmu_disable()
{
	uint32_t cr = __mmu_getcr();
	cr &= ~MMU_CR_ENABLE;
	__mmu_setcr(cr);
}
#endif
