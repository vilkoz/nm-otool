#include <sys/types.h>
#include "qsort_private.h"

static void		swap(void *a, void *b, size_t size)
{
	int			i;
	char		t;

	i = -1;
	while (++i < (int)size)
	{
		t = ((char*)a)[i];
		((char*)a)[i] = ((char*)b)[i];
		((char*)b)[i] = t;
	}
}

static int		partition(t_array_slice s, int (*cmp)(const void*, const void*))
{
	void	*pivot;
	int		i;
	int		j;

	pivot = (void*)(((char *)s.base) + (s.high * s.size));
	i = s.low - 1;
	j = s.low - 1;
	while (++j <= s.high - 1)
	{
		if (cmp((void*)(((char *)s.base) + (j * s.size)), pivot) < 0)
		{
			i++;
			swap((void*)(((char *)s.base) + (i * s.size)),
				(void*)(((char *)s.base) + (j * s.size)), s.size);
		}
	}
	swap((void*)(((char *)s.base) + ((i + 1) * s.size)),
		(void*)(((char *)s.base) + (s.high * s.size)), s.size);
	return (i + 1);
}

static void		quick_sort(t_array_slice s, int (*cmp)(const void*, const void*))
{
	int		pi;

	if (s.low >= s.high)
		return ;
	pi = partition(s, cmp);
	quick_sort((t_array_slice){s.base, s.size, s.low, pi - 1}, cmp);
	quick_sort((t_array_slice){s.base, s.size, pi + 1, s.high}, cmp);
}

void			ft_qsort(void *base, size_t nelem, size_t size,
					int (*cmp)(const void*, const void*))
{
	quick_sort((t_array_slice){base, size, 0, nelem - 1}, cmp);
}
