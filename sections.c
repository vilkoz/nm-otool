#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include "libft.h"

static char 	**g_sections = NULL;
static size_t	g_n_sections = 0;

char	**get_sections(void)
{
	return (g_sections);
}

void	append_section(struct section_64 *sect)
{
	g_sections = ft_realloc(g_sections, sizeof(char*) * (g_n_sections),
		sizeof(char*) * (g_n_sections + 1));
	g_sections[g_n_sections] = sect->sectname;
	g_n_sections++;
}

void	save_sections(struct segment_command_64 *seg)
{
	int					i;
	struct section_64	*sec_table;

	sec_table = (struct section_64*)((void*)seg +
		sizeof(struct segment_command_64));
	i = -1;
	while (++i < (int)seg->nsects)
	{
		append_section(sec_table + i);
	}
}
