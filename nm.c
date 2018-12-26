#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

#include <string.h> //strcmp

#define ERROR(x) {fprintf(stderr, x "\n"); return(EXIT_FAILURE);}

static char 	**g_sections = NULL;
static size_t	g_n_sections = 0;

char	get_section_char(uint8_t n_sect)
{
	const char		*names[] = {
		"__text",
		"__data",
		"__bss"
	};
	const char		labels[] = {
		'T',
		'D',
		'B'
	};
	char			*sect_name;
	int				i;

	sect_name = g_sections[n_sect - 1];
	i = -1;
	while (++i < (int)(sizeof(labels) / sizeof(labels[0])))
	{
		if (!strcmp(names[i], sect_name))
			return (labels[i]);
	}
	return ('?');
}

char	get_type(struct nlist_64 *entry)
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

	i = -1;
	while (++i < (int)(sizeof(labels) / sizeof(labels[0])))
	{
		if ((entry->n_type & N_TYPE) == values[i])
			return (labels[i]);
	}
	if (entry->n_sect != NO_SECT)
		return (get_section_char(entry->n_sect));
	return ('?');
}

void	print_symtab(struct symtab_command *sym, char *ptr)
{
	struct nlist_64		*nlist;
	char				*string_array;
	int					i;

	nlist = (void*)ptr + sym->symoff;
	string_array = (void*)ptr + sym->stroff;
	i = -1;
	while (++i < (int)sym->nsyms)
	{
		if (nlist[i].n_type & N_STAB)
			continue ;
		printf("%c %s\n", get_type((void*)(&(nlist[i]))), string_array + nlist[i].n_un.n_strx);
		if (nlist[i].n_sect != NO_SECT)
			printf("\tsection: %s\n", g_sections[nlist[i].n_sect-1]);
	}
}

void	append_section(struct section_64 *sect)
{
	g_sections = realloc(g_sections, sizeof(char*) * (g_n_sections + 1));
	g_sections[g_n_sections] = sect->sectname;
	g_n_sections++;
}

void	print_sections(struct segment_command_64 *seg)
{
	int					i;
	struct section_64	*sec_table;

	sec_table = (struct section_64*)((void*)seg + sizeof(struct segment_command_64));
	i = -1;
	while (++i < (int)seg->nsects)
	{
		append_section(sec_table + i);
	}
}

void	handle_64(char *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;

	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = (void*)ptr + sizeof(struct mach_header_64);
	i = -1;
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			struct symtab_command	*smtab;
			smtab = (struct symtab_command*)lc;
			print_symtab(smtab, ptr);
			break ;
		} else if (lc->cmd == LC_SEGMENT_64)
		{
			struct segment_command_64	*segment = (struct segment_command_64*)lc;
			printf("segname: %s\n", segment->segname);
			print_sections(segment);
		}
		lc = (void*)lc + lc->cmdsize;
	}
}

void	nm(char *ptr)
{
	uint32_t	magic_num;

	magic_num = *(int*)ptr;
	if (magic_num == MH_MAGIC_64)
		handle_64(ptr);
}

int		main(int ac, char **av)
{
	int				fd;
	char			*ptr;
	struct stat		file_stat;

	if (ac != 2)
		ERROR("NO ARGUMENT");
	if ((fd = open(av[1], O_RDONLY)) < 0)
		ERROR("Can't open file");
	if (fstat(fd, &file_stat) < 0)
		ERROR("Can't stat file");
	if ((ptr = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		ERROR("mmap error");
	nm(ptr);
	if (munmap(ptr, file_stat.st_size) < 0)
		ERROR("munmap error");
	return (EXIT_SUCCESS);
}
