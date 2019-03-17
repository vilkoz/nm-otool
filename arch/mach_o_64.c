#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include <stdio.h> //printf
#include "sections.h"
#include "libft.h"
#include "symbol_entry.h"
#include "common.h"

static t_vector	*fill_symbol_entries(struct symtab_command *sym, char *ptr)
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
			get_section_type((nlist + i)->n_type, (nlist + i)->n_sect));
		vector_add(l, (void*)tmp);
		free(tmp);
	}
	return (l);
}

static int	sort_function(const void *a, const void* b)
{
	char	*name1;
	char	*name2;
	int		res;

	name1 = ((t_symbol_entry_64*)a)->name;
	name2 = ((t_symbol_entry_64*)b)->name;
	res = ft_strcmp(name1, name2);
	if (res != 0)
		return (res);
	return (((t_symbol_entry_64*)a)->nlist_entry->n_value -
		((t_symbol_entry_64*)b)->nlist_entry->n_value);
}

static void	print_symtab(struct symtab_command *sym, char *ptr)
{
	t_vector			*v;
	int					i;
	t_symbol_entry_64	*tmp;
	uint8_t				type;

	v = fill_symbol_entries(sym, ptr);
	v = sort_symbol_entries(v, sizeof(t_symbol_entry_64), &sort_function);
	i = -1;
	while (++i < (int)v->size)
	{
		VECTOR_GET_TO(tmp, v, i);
		type = tmp->nlist_entry->n_type;
		if ((type & N_TYPE) == N_UNDF || (type & N_TYPE) == N_INDR)
			ft_putstr("                ");
		else
			ft_puthex_fill(tmp->nlist_entry->n_value, '0', 16);
		ft_putchar(' ');
		ft_putchar(tmp->type);
		ft_putchar(' ');
/*
<                  I _krb5_get_init_creds_opt_set_salt (indirect for _krb5_get_init_creds_opt_set_salt)
---
> 0000000000003cb1 I _krb5_get_init_creds_opt_set_salt
*/
		ft_putstr(tmp->name);
		if ((type & N_TYPE) == N_INDR)
		{
			ft_putstr(" (indirect for ");
			ft_putstr(tmp->name);
			ft_putendl(")");
		}
		else
			ft_putchar('\n');
	}
	vector_delete(&v, NULL);
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
			save_sections_64((struct segment_command_64*)lc);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	free_sections();
}
