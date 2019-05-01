#include <stdint.h>
#include <stdio.h>
#include <mach-o/fat.h>
#include "safe_ptr.h"
#include "endian.h"
#include "arch_private.h"

void handle_fat_binary(void *ptr, const char *filename)
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
					be2le(fat_elem->size)), (char*)filename);
		fat_elem++;
	}
}

void handle_fat_binary_64(void *ptr, const char *filename)
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
					be2le64(fat_elem->size)), (char*)filename);
		fat_elem++;
	}
}
