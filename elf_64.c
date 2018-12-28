#include <stdlib.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include <stdio.h> //printf
#include "sections.h"
#include "libft.h"

char	get_section_char(uint8_t n_sect)
{
	const char		*names[] = {
		"__text",
		"__data",
		"__bss",
		"__const"
	};
	const char		labels[] = {
		'T',
		'D',
		'b',
		's'
	};
	char			*sect_name;
	int				i;

	sect_name = get_sections()[n_sect - 1];
	i = -1;
	while (++i < (int)(sizeof(labels) / sizeof(labels[0])))
	{
		if (!ft_strcmp(names[i], sect_name))
			return (labels[i]);
	}
	return ('?');
}

char	get_type(struct nlist_64 *entry)
{
	const char		labels[] = {
		'U',
		'A',
		'I'
		};
	const uint16_t	values[] = {
		N_UNDF,
		N_ABS,
		N_INDR
		};
	int				i;

	i = -1;
	while (++i < (int)(sizeof(labels) / sizeof(labels[0])))
	{
		if ((entry->n_type & N_TYPE) == values[i])
			return (labels[i]);
	}
	if (entry->n_sect != NO_SECT)
		return (get_section_char(entry->n_sect));
	return ('?');
}

void	print_symtab(struct symtab_command *sym, char *ptr)
{
	struct nlist_64		*nlist;
	char				*string_array;
	int					i;

	nlist = (void*)ptr + sym->symoff;
	string_array = (void*)ptr + sym->stroff;
	i = -1;
	while (++i < (int)sym->nsyms)
	{
		if (nlist[i].n_type & N_STAB)
			continue ;
		if ((nlist[i].n_type & N_TYPE) == N_UNDF)
		{
			ft_putstr("                 ");
			ft_putchar(get_type((void*)(&(nlist[i]))));
			ft_putchar(' ');
			ft_putendl(string_array + nlist[i].n_un.n_strx);
		}
		else
		{
			ft_puthex_fill(nlist[i].n_value, '0', 16);
			ft_putchar(' ');
			ft_putchar(get_type((void*)(&(nlist[i]))));
			ft_putchar(' ');
			ft_putendl(string_array + nlist[i].n_un.n_strx);
		}
	}
}

void	handle_64(char *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = (void*)ptr + sizeof(struct mach_header_64);
	i = -1;
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			struct symtab_command	*smtab;
			smtab = (struct symtab_command*)lc;
			print_symtab(smtab, ptr);
			break ;
		} else if (lc->cmd == LC_SEGMENT_64)
		{
			save_sections((struct segment_command_64*)lc);
		}
		lc = (void*)lc + lc->cmdsize;
	}
}
