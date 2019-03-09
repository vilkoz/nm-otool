#ifndef COMMON_H
# define COMMON_H

char		get_section_type(uint8_t n_type, uint8_t n_sect);
t_vector	*sort_symbol_entries(t_vector *v, size_t elem_size,
				int (*sort_function)(const void*, const void*));

#endif
