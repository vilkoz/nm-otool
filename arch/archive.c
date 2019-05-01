#include <ar.h>
#include "libft.h"
#include "safe_ptr.h"
#include "arch_private.h"

static void parse_ar_header(char **ptr)
{
	struct ar_hdr	*hdr;
	size_t 			offset;

	hdr = (struct ar_hdr*)safe_ptr((*ptr + 8), sizeof(struct ar_hdr) + 20);
	if (hdr == NULL)
	{
		*ptr = NULL;
		return ;
	}
	offset = ft_atoi(&(hdr->ar_size[0]));
	*ptr = safe_ptr((char*)hdr + offset + sizeof(struct ar_hdr),
		20 + sizeof(struct ar_hdr));
}

static void	print_entry_header(const char *filename, const char *sym_name)
{
	ft_putchar('\n');
	ft_putstr(filename);
	ft_putchar('(');
	ft_putstr(sym_name);
	ft_putstr("):\n");
}

static void	proccess_ar_endry(char **ptr, const char *filename)
{
	struct ar_hdr	*hdr;
	size_t 			offset;
	char			*sym_name;
	size_t			longname_size;

	hdr = (struct ar_hdr*)(*ptr);
	offset = ft_atoi(&(hdr->ar_size[0]));
	if (ft_strncmp(&(hdr->ar_name[0]), "#1/", 3) != 0)
	{
		ft_putstr_fd("nm: ar: ar_name type not supported\n", 2);
		longname_size = 20;
	}
	else
	{
		longname_size = ft_atoi(&(hdr->ar_name[0]) + 3);
		sym_name = (*ptr + sizeof(struct ar_hdr));
		print_entry_header(filename, sym_name);
	}
	nm(safe_ptr(*ptr + sizeof(struct ar_hdr) + longname_size,
			offset - sizeof(struct ar_hdr) - longname_size), (char*)filename);
	*ptr = safe_ptr(*ptr + offset + sizeof(struct ar_hdr),
		20 + sizeof(struct ar_hdr));
}

void		handle_archive(char *ptr, const char *filename)
{
	parse_ar_header(&ptr);
	if (ptr == NULL)
	{
		ft_putstr_fd("nm: ar: error parsing ar_header\n", 2);
		return ;
	}
	while (1)
	{
		proccess_ar_endry(&ptr, filename);
		if (ptr == NULL)
			break ;
	}
}
