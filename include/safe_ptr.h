#ifndef SAFE_PTR_H
# define SAFE_PTR_H

# include <stdarg.h>

void	set_file_size(size_t fs);
size_t	get_file_size(void);
void	set_safe_ptr_base(void *base);
void	*safe_ptr(void *ptr, size_t region_size);
void	clear_safe_ptr(void);

#endif
