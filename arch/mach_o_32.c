#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include "sections.h"
#include "libft.h"
#include "symbol_entry.h"
#include "common.h"
#include "otool.h"

static t_vector	*fill_symbol_entries(struct symtab_command *sym, char *ptr)
{
	t_vector			*l;
	struct nlist		*nlist;
	char				*string_array;
	int					i;

	l = vector_new(NULL, 0, sizeof(t_symbol_entry_32));
	nlist = (void*)ptr + sym->symoff;
	string_array = (void*)ptr + sym->stroff;
	i = -1;
	while (++i < (int)sym->nsyms)
	{
		t_symbol_entry_32	*tmp;

		if (nlist[i].n_type & N_STAB)
			continue ;
		tmp = new_s_symbol_entry_32(nlist + i,
			string_array + nlist[i].n_un.n_strx,
			get_section_type((nlist + i)->n_type, (nlist + i)->n_sect));
		vector_add(l, (void*)tmp);
		free(tmp);
	}
	return (l);
}

static int		sort_function(const void *a, const void* b)
{
	char	*name1;
	char	*name2;
	int		res;

	name1 = ((t_symbol_entry_32*)a)->name;
	name2 = ((t_symbol_entry_32*)b)->name;
	res = ft_strcmp(name1, name2);
	if (res != 0)
		return (res);
	return (((t_symbol_entry_32*)a)->nlist_entry->n_value -
		((t_symbol_entry_32*)b)->nlist_entry->n_value);
}

static void		print_symtab(struct symtab_command *sym, char *ptr)
{
	t_vector			*v;
	int					i;
	t_symbol_entry_32	*tmp;

	v = fill_symbol_entries(sym, ptr);
	v = sort_symbol_entries(v, sizeof(t_symbol_entry_32), &sort_function);
	i = -1;
	while (++i < (int)v->size)
	{
		VECTOR_GET_TO(tmp, v, i);
		if ((tmp->nlist_entry->n_type & N_TYPE) == N_UNDF)
			ft_putstr("        ");
		else
			ft_puthex_fill(tmp->nlist_entry->n_value, '0', 8);
		ft_putchar(' ');
		ft_putchar(tmp->type);
		ft_putchar(' ');
		ft_putendl(tmp->name);
	}
	vector_delete(&v, NULL);
}

void			handle_32(char *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header		*header;
	struct load_command		*lc;

	header = (struct mach_header*)ptr;
	ncmds = header->ncmds;
	lc = (void*)ptr + sizeof(struct mach_header);
	i = -1;
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			if (!get_otool_mode())
				print_symtab((struct symtab_command*)lc, ptr);
			break ;
		} else if (lc->cmd == LC_SEGMENT)
		{
			if (get_otool_mode())
				otool_print_text_section_32((struct segment_command*)lc, ptr);
			else
				save_sections_32((struct segment_command*)lc);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	free_sections();
}
