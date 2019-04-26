#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include "libft.h"
#include "otool.h"

static char 	**g_sections = NULL;
static size_t	g_n_sections = 0;

char		**get_sections(void)
{
	return (g_sections);
}

static void	append_section(char *sectname)
{
	g_sections = ft_realloc(g_sections, sizeof(char*) * (g_n_sections),
		sizeof(char*) * (g_n_sections + 1));
	g_sections[g_n_sections] = sectname;
	g_n_sections++;
}

void		save_sections_64(struct segment_command_64 *seg)
{
	int					i;
	struct section_64	*sec_table;
	struct section_64	*sect;

	sec_table = (struct section_64*)((void*)seg +
		sizeof(struct segment_command_64));
	i = -1;
	while (++i < (int)seg->nsects)
	{
		sect = sec_table + i;
		append_section(sect->sectname);
	}
}

void		save_sections_32(struct segment_command *seg)
{
	int					i;
	struct section	*sec_table;
	struct section	*sect;

	sec_table = (struct section*)((void*)seg +
		sizeof(struct segment_command));
	i = -1;
	while (++i < (int)seg->nsects)
	{
		sect = sec_table + i;
		append_section(sect->sectname);
	}
}

void		free_sections(void)
{
	if (g_sections)
	{
		free(g_sections);
		g_sections = NULL;
		g_n_sections = 0;
	}
}
