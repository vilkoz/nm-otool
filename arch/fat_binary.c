#include <stdint.h>
#include <stdio.h>
#include <mach-o/fat.h>
#include "safe_ptr.h"
#include "endian.h"

#define CPU_SUBTYPE_X86_ALL		((cpu_subtype_t)3) // TODO: where to put dis

void	nm(char *ptr, const char *filename);

void handle_fat_binary(void *ptr)
{
	struct fat_header	*hdr;
	struct fat_arch		*fat_elem;
	int					i;

	hdr = ptr;
	fat_elem = ptr + sizeof(struct fat_header);
	i = -1;
	while (++i < (int)be2le(hdr->nfat_arch))
	{
		if (be2le(fat_elem->cputype) == 0x10007 &&
				(fat_elem->cpusubtype >> 24) == CPU_SUBTYPE_X86_ALL)
			nm(safe_ptr(ptr + be2le(fat_elem->offset),
					be2le(fat_elem->size)), 0);
		fat_elem++;
	}
}

void handle_fat_binary_64(void *ptr)
{
	struct fat_header	*hdr;
	struct fat_arch_64	*fat_elem;
	int					i;

	hdr = ptr;
	fat_elem = ptr + sizeof(struct fat_header);
	i = -1;
	while (++i < (int)be2le(hdr->nfat_arch))
	{
		if (be2le(fat_elem->cputype) == 0x10007 &&
				(fat_elem->cpusubtype >> 24) == CPU_SUBTYPE_X86_ALL)
			nm(safe_ptr(ptr + be2le64(fat_elem->offset),
					be2le64(fat_elem->size)), 0);
		fat_elem++;
	}
}
