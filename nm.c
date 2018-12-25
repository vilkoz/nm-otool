#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>

#define ERROR(x) {fprintf(stderr, x "\n"); return(EXIT_FAILURE);}

void	print_symtab(struct symtab_command *sym, char *ptr)
{
	struct nlist_64		*nlist;
	char				*string_array;
	int					i;

	nlist = (void*)ptr + sym->symoff;
	string_array = ptr + sym->stroff;
	i = -1;
	while (++i < sym->nsyms)
	{
		printf("%s\n", string_array + nlist[i].n_un.n_strx);
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
		}
		lc = (void*)lc + lc->cmdsize;
	}
}

void	nm(char *ptr)
{
	int		magic_num;

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
	if ((ptr = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		ERROR("mmap error");
	nm(ptr);
	if (munmap(ptr, file_stat.st_size) < 0)
		ERROR("munmap error");
	return (EXIT_SUCCESS);
}