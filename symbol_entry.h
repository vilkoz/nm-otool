#ifndef SYMBOL_ENTRY_H
# define SYMBOL_ENTRY_H

typedef struct				s_symbol_entry_64
{
	struct nlist_64			*nlist_entry;
	char					*name;
	char					type;
}							t_symbol_entry_64;

struct s_symbol_entry_64	*new_s_symbol_entry_64(struct nlist_64 *nlist_entry,
								char *name, char type);
#endif
