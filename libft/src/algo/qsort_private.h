#ifndef QSORT_PRIVATE_H
# define QSORT_PRIVATE_H

#include <sys/types.h>

typedef struct		s_array_slice
{
	void			*base;
	size_t			size;
	int				low;
	int				high;
}					t_array_slice;

#endif
