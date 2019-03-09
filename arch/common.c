#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include "sections.h"
#include "libft.h"
#include "symbol_entry.h"

#define IS_EXTERNAL(a) ((a) & N_EXT) // TODO: figure out where to place this

static char	get_section_char(uint8_t n_sect)
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
		'B',
		'S'
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
	return ('S');
}

char		get_section_type(uint8_t n_type, uint8_t n_sect)
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
	char			res;

	i = -1;
	while (++i < (int)(sizeof(labels) / sizeof(labels[0])))
	{
		if ((n_type & N_TYPE) == values[i])
			return (labels[i]);
	}
	if (n_sect != NO_SECT)
	{
		res = get_section_char(n_sect);
		return (IS_EXTERNAL(n_type) ? res : ft_tolower(res));
	}
	return ('?');
}

t_vector	*sort_symbol_entries(t_vector *v, size_t elem_size,
				int (*sort_function)(const void*, const void*))
{
	ft_qsort(v->elems, v->size, elem_size, sort_function);
	return (v);
}
