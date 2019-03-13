#include <stdint.h>
#include <stdio.h>
#include <mach-o/fat.h>
#include "safe_ptr.h"

//#define DEBUG
#ifdef DEBUG
# define print_elem(s, e) \
	printf(#e": %i ", be2le(s->e));
#else
# define print_elem(s, e)
#endif

void	nm(char *ptr, const char *filename);

uint32_t be2le(uint32_t i)
{
	return (
			(((i & (0xff << 0))) << 16) |
			(((i & (0xff << 8))) << 8) |
			(((i & (0xff << 16))) >> 8) |
			(((i & (0xff << 24))) >> 24)
			);
}

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
		if (be2le(fat_elem->cputype) == 0x10007)
			nm(safe_ptr(ptr + be2le(fat_elem->offset), be2le(fat_elem->size)), 0);
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
		if (be2le(fat_elem->cputype) == 0x10007)
			nm(safe_ptr(ptr + be2le(fat_elem->offset), be2le(fat_elem->size)), 0);
		fat_elem++;
	}
}
