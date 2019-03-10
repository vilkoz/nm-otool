#include <stdio.h> // printf
#include <ar.h>
#include "libft.h"

void	nm(char *ptr, char *filename);

void print_byte_string(char *str, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		putchar(str[i]);
	}
}

#define print_field(h, n, s) \
	printf(#n": "); \
	print_byte_string(h->n, s); \
	putchar(' ');

struct test {
	uint32_t	a;
	uint32_t	b;
};

static void parse_ar_header(char **ptr, size_t *num)
{
	struct ar_hdr	*hdr;
	size_t 			offset;

	hdr = (struct ar_hdr*)(*ptr + 8);
	//print_field(hdr, ar_name, 16);
	//print_field(hdr, ar_date, 12);
	//print_field(hdr, ar_uid, 6);
	//print_field(hdr, ar_gid, 6);
	//print_field(hdr, ar_mode, 8);
	//print_field(hdr, ar_size, 10);
	//print_field(hdr, ar_fmag, 2);
	//puts("");
	sscanf(&(hdr->ar_size[0]), "%zu", &offset);
	*num = *(uint64_t*)(*ptr + sizeof(struct ar_hdr) + 20 + 8) / 8;
	printf("sizeof(struct ar_hdr): %zu\n",sizeof(struct ar_hdr));
	printf("num: %zu\n", *num);
	printf("sizeof: %zu\n", sizeof(struct test) );
	*ptr += offset + sizeof(struct ar_hdr);
}

static void print_header(char **ptr, const char *filename)
{
	struct ar_hdr	*hdr;
	size_t 			offset;
	char			*sym_name;

	hdr = (struct ar_hdr*)(*ptr + 8);
	//print_field(hdr, ar_name, 16);
	//print_field(hdr, ar_date, 12);
	//print_field(hdr, ar_uid, 6);
	//print_field(hdr, ar_gid, 6);
	//print_field(hdr, ar_mode, 8);
	//print_field(hdr, ar_size, 10);
	//print_field(hdr, ar_fmag, 2);
	//puts("");
	sscanf(&(hdr->ar_size[0]), "%zu", &offset);
	//printf("size: %zu\n", offset);
	ft_putstr("\n");
	ft_putstr(filename);
	ft_putstr("(");
	sym_name = (char*)(*ptr + 8 + sizeof(struct ar_hdr));
	ft_putstr(sym_name);
	ft_putstr("):\n");
	//puts("");
	nm(*ptr + 8 + sizeof(struct ar_hdr) + 20, 0);
	*ptr += offset + sizeof(struct ar_hdr);
}

void	handle_archive(char *ptr, const char *filename)
{
	size_t		num;
	int			i;

	num = 0;
	parse_ar_header(&ptr, &num);
	i = -1;
	while (++i < (int)num)
		print_header(&ptr, filename);
}
