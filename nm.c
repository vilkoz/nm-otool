#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>
#include "elf_64.h"
#include <mach-o/loader.h>

#define ERROR(x) {fprintf(stderr, x "\n"); return(EXIT_FAILURE);}

void	nm(char *ptr)
{
	uint32_t	magic_num;

	magic_num = *(int*)ptr;
	if (magic_num == MH_MAGIC_64)
		handle_64(ptr);
	else
		fprintf(stderr, "File format is not supported\n");
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
