#include <stdlib.h>

static size_t		g_file_size = 0;
static void			*g_safe_ptr_base = NULL;

void	set_file_size(size_t fs)
{
	g_file_size = fs;
}

size_t	get_file_size(void)
{
	return g_file_size;
}

void	set_safe_ptr_base(void *base)
{
	g_safe_ptr_base = base;
}

void	*safe_ptr(void *ptr, size_t region_size)
{
	if (g_file_size == 0)
		return (NULL);
	if (g_safe_ptr_base == NULL)
		return (NULL);
	if (ptr == NULL)
		return (NULL);
	if (ptr - g_safe_ptr_base + (int64_t)region_size > (int64_t)g_file_size)
		return (NULL);
	return (ptr);
}

