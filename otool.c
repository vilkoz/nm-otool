#include <mach-o/loader.h>
#include "libft.h"
#include "safe_ptr.h"

static int		g_otool_mode = 0;

void			set_otool_mode(int mode)
{
	g_otool_mode = mode;
}

int				get_otool_mode(void)
{
	return (g_otool_mode);
}
#include <stdio.h>
void			print_text_section(struct section_64 *sect)
{
	const void	*ptr = safe_ptr_base(NULL);
	const char	*text_start = safe_ptr((char*)ptr + sect->offset, sect->size);
	int			i;

	if (!text_start)
		return (ft_putstr_fd("ft_otool: section > file size\n", 2));
	i = -1;
	while (++i < (int)sect->size)
	{
		if (i % 16 == 0)
		{
			ft_putchar('\n');
			ft_puthex_fill((uint64_t)(sect->addr + i), '0', 16);
			ft_putstr("\t");
		}
		ft_puthex_fill((unsigned char)*(text_start + i), '0', 2);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}
