#include <stdio.h> //fprintf
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>
#include <mach-o/loader.h>
#include <mach-o/fat.h>
#include <ar.h>
#include "arch.h"
#include "libft.h"
#include "safe_ptr.h"
#include "otool.h"

#define ERROR(x) {fprintf(stderr, x "\n"); return(EXIT_FAILURE);}

static void		print_otool_filename(uint64_t magic_num, const char *filename)
{
	const uint64_t	magic_nums[] = { MH_MAGIC_64, MH_CIGAM_64, MH_MAGIC,
		MH_CIGAM
	};
	int				i;

	i = -1;
	while (++i < (int)(sizeof(magic_nums) / sizeof(magic_nums[0])))
	{
		if (magic_num == magic_nums[i])
		{
			ft_putstr(filename);
			ft_putstr(":\nContents of (__TEXT,__text) section");
			return ;
		}
	}
}

void			nm(char *ptr, const char *filename)
{
	uint64_t	magic_num;

	if (ptr == NULL)
		return ;
	magic_num = *(uint32_t*)ptr;
	if (get_otool_mode())
		print_otool_filename(magic_num, filename);
	if (magic_num == MH_MAGIC_64 || magic_num == MH_CIGAM_64)
		handle_64(ptr);
	else if (magic_num == MH_MAGIC || magic_num == MH_CIGAM)
		handle_32(ptr);
	else if (magic_num == FAT_MAGIC || magic_num == FAT_CIGAM)
		handle_fat_binary(ptr);
	else if (magic_num == FAT_MAGIC_64 || magic_num == FAT_CIGAM_64)
		handle_fat_binary_64(ptr);
	else
	{
		magic_num = *(uint64_t*)ptr;
		if (ft_strncmp((char*)&magic_num, ARMAG, SARMAG) == 0)
			handle_archive(ptr, filename);
		else
			fprintf(stderr, "MY_NM: File format is not supported 0x%016llx\n", magic_num);
	}
}

int				process_file(const char *filename)
{
	int				fd;
	char			*ptr;
	struct stat		file_stat;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ERROR("Can't open file");
	if (fstat(fd, &file_stat) < 0)
		ERROR("Can't stat file");
	if ((ptr = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		ERROR("mmap error");
	set_file_size(file_stat.st_size);
	safe_ptr_base(ptr);
	nm(ptr, filename);
	clear_safe_ptr();
	if (munmap(ptr, file_stat.st_size) < 0)
		ERROR("munmap error");
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	int		i;

	if (ac < 2)
	{
		process_file("./a.out");
		return (EXIT_SUCCESS);
	}
	if (!ft_strncmp(av[0], "ft_otool", sizeof("ft_otool")) ||
			!ft_strncmp(av[0], "./ft_otool", sizeof("./ft_otool")))
		set_otool_mode(1);
	i = 0;
	while (++i < ac)
		process_file(av[i]);
	return (EXIT_SUCCESS);
}
