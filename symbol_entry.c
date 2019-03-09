#include "symbol_entry.h"
#include "libft.h"

struct s_symbol_entry_64	*new_s_symbol_entry_64(struct nlist_64 *nlist_entry,
								char *name, char type)
{
	struct s_symbol_entry_64	*e;

	e = ft_memalloc(sizeof(struct s_symbol_entry_64));
	e->nlist_entry = nlist_entry;
	e->name = name;
	e->type = type;
	return (e);
}

struct s_symbol_entry_32	*new_s_symbol_entry_32(struct nlist *nlist_entry,
								char *name, char type)
{
	struct s_symbol_entry_32	*e;

	e = ft_memalloc(sizeof(struct s_symbol_entry_32));
	e->nlist_entry = nlist_entry;
	e->name = name;
	e->type = type;
	return (e);
}
