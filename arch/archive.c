#include <stdio.h> // printf
#include <ar.h>
#include "libft.h"
#include "safe_ptr.h"

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

static void parse_ar_header(char **ptr)
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
	//printf("sizeof(struct ar_hdr): %zu\n",sizeof(struct ar_hdr));
	*ptr = (char*)hdr +  offset + sizeof(struct ar_hdr);
}

static void print_header(char **ptr, const char *filename)
{
	struct ar_hdr	*hdr;
	size_t 			offset;
	char			*sym_name;
	size_t			longname_size;

	hdr = (struct ar_hdr*)(*ptr);
	//print_field(hdr, ar_name, 16);
	//print_field(hdr, ar_date, 12);
	//print_field(hdr, ar_uid, 6);
	//print_field(hdr, ar_gid, 6);
	//print_field(hdr, ar_mode, 8);
	//print_field(hdr, ar_size, 10);
	//print_field(hdr, ar_fmag, 2);
	//puts("");
	sscanf(&(hdr->ar_size[0]), "%zu", &offset);
	sscanf(&(hdr->ar_name[0]), "#1/%zu", &longname_size);
	//printf("size: %zu\n", offset);
	ft_putstr("\n");
	ft_putstr(filename);
	ft_putstr("(");
	sym_name = (char*)(*ptr + sizeof(struct ar_hdr));
	ft_putstr(sym_name);
	ft_putstr("):\n");
	nm(*ptr + sizeof(struct ar_hdr) + longname_size, 0);
	*ptr = safe_ptr(*ptr + offset + sizeof(struct ar_hdr),
		20 + sizeof(struct ar_hdr));
}

void	handle_archive(char *ptr, const char *filename)
{
	parse_ar_header(&ptr);
	while (1)
	{
		print_header(&ptr, filename);
		if (ptr == NULL)
			break ;
	}
}
