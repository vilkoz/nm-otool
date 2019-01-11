#include <stdlib.h> //qsort
// TODO: write own qsort
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

//#include <stdio.h> //printf
#include "sections.h"
#include "libft.h"
#include "symbol_entry.h"

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

t_vector	*fill_symbol_entries(struct symtab_command *sym, char *ptr)
{
	t_vector			*l;
	struct nlist_64		*nlist;
	char				*string_array;
	int					i;

	l = vector_new(NULL, 0, sizeof(t_symbol_entry_64));
	nlist = (void*)ptr + sym->symoff;
	string_array = (void*)ptr + sym->stroff;
	i = -1;
	while (++i < (int)sym->nsyms)
	{
		t_symbol_entry_64	*tmp;

		if (nlist[i].n_type & N_STAB)
			continue ;
		tmp = new_s_symbol_entry_64(nlist + i,
			string_array + nlist[i].n_un.n_strx,
			get_type((void*)(&(nlist[i]))));
		vector_add(l, (void*)tmp);
	}
	return (l);
}

static int	sort_function(const void *a, const void* b)
{
	char	*name1;
	char	*name2;

	name1 = ((t_symbol_entry_64*)a)->name;
	name2 = ((t_symbol_entry_64*)b)->name;
	return (ft_strcmp(name1, name2));
}

void			ft_qsort(void *base, size_t nelem, size_t size, int (*cmp)(const void*, const void*));

t_vector	*sort_symbol_entries(t_vector *v)
{
	ft_qsort(v->elems, v->size, sizeof(t_symbol_entry_64), &sort_function);
	return (v);
}

void	print_symtab(struct symtab_command *sym, char *ptr)
{
	t_vector			*v;
	int					i;
	t_symbol_entry_64	*tmp;

	v = fill_symbol_entries(sym, ptr);
	v = sort_symbol_entries(v);
	i = -1;
	while (++i < (int)v->size)
	{
		VECTOR_GET_TO(tmp, v, i);
		if ((tmp->nlist_entry->n_type & N_TYPE) == N_UNDF)
			ft_putstr("                ");
		else
			ft_puthex_fill(tmp->nlist_entry->n_value, '0', 16);
		ft_putchar(' ');
		ft_putchar(tmp->type);
		ft_putchar(' ');
		ft_putendl(tmp->name);
	}
}

#include <stdio.h>

unsigned int		read_uleb(char **uleb128)
{
	unsigned int		res;
	int					shift;
	char				byte;

	res = 0;
	shift = 0;
	while (1)
	{
		byte = *((*uleb128)++);
		res |= (byte & 0x7f) << shift;
		if (((byte & 0x80) >> 7) == 0)
			break ;
		shift += 7;
	}
	return res;
}

void	print_node(char *offset, char *start, size_t trie_size)
{
	char		branches;
	int			child_offset;
	int			i;
	int			terminal_size;

	if (offset >= start + trie_size)
		return ;
	printf("%p node: %x\n", offset, offset[0]);
	if (offset[0] == 0)
	{
		branches = (++offset)[0];
		printf("BRANCHES: %d\n", branches);
		i = -1;
		while (++i < branches)
		{
			printf("branch %d: ", i);
			while (*(++offset) != 0)
				printf("%c", offset[0]);
			puts("");
			++offset;
			child_offset = read_uleb(&offset);
			print_node(start + child_offset, start, trie_size);
		}
	}
	else
	{
		terminal_size = read_uleb(&offset);
		printf("TERM\nflags: 0x%x ", *offset);
		offset++;
		terminal_size = read_uleb(&offset);
		printf("offset: 0x%x\n", terminal_size);
		++offset;
		terminal_size = read_uleb(&offset);
		printf(" child nodes: %d\n", terminal_size);
	}
}

void	handle_dysymtab(struct dyld_info_command* dysym, char *ptr)
{
	char		*export;
	size_t		export_size;

	export = ptr + dysym->export_off;
	export_size = dysym->export_size;
	printf("export: %p, %zu\n", export, export_size);
	print_node(export, export, export_size);
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
		printf("lc->cmd: 0x%x\n", lc->cmd);
		if (lc->cmd == LC_SYMTAB)
		{
			struct symtab_command	*smtab;
			smtab = (struct symtab_command*)lc;
			print_symtab(smtab, ptr);
			break ;
		}
		else if (lc->cmd == LC_SEGMENT_64)
			save_sections((struct segment_command_64*)lc);
		else if (lc->cmd == LC_DYLD_INFO_ONLY)
		{
			handle_dysymtab((struct dyld_info_command*)lc, ptr);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	free_sections();
}
