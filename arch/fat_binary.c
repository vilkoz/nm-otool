#include <stdint.h>
#include <stdio.h>

struct fat_hdr
{
	uint32_t	magic_num;
	uint32_t	ar_num;
};

struct fat_elem_hdr
{
	uint32_t	cpu_type;
	uint32_t	cpu_subtype;
	uint32_t	ar_offset;
	uint32_t	ar_size;
	uint32_t	is_aligned;
};

#define print_elem(s, e) \
	printf(#e": %i ", be2le(s->e));

uint32_t be2le(uint32_t i)
{
	return (
			(((i & (0xff << 0))) << 16) |
			(((i & (0xff << 8))) << 8) |
			(((i & (0xff << 16))) >> 8) |
			(((i & (0xff << 24))) >> 24)
			);
}

void	nm(char *ptr, const char *filename);

void handle_fat_binary(void *ptr)
{
	struct fat_hdr *hdr;
	struct fat_elem_hdr *fat_elem;

	hdr = ptr;
	print_elem(hdr, ar_num);
	puts("");
	printf("le2be num: %x\n", be2le(hdr->ar_num));
	fat_elem = ptr + sizeof(struct fat_hdr);
	for (size_t i=0; i < be2le(hdr->ar_num); i++)
	{
		print_elem(fat_elem, cpu_type);
		print_elem(fat_elem, cpu_subtype);
		print_elem(fat_elem, ar_offset);
		print_elem(fat_elem, ar_size);
		print_elem(fat_elem, is_aligned);
		puts("");
		nm(ptr + be2le(fat_elem->ar_offset), 0);
		fat_elem++;
	}
}
