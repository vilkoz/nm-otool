#include <mach-o/loader.h>
#include "libft.h"
#include "safe_ptr.h"

#define OTOOL_PTR_LEN (8)
#define HEX_BYTE_LEN (2)
#define BYTE_IN_LINE_COUNT (16)

static void		prepare_buffer(char *buf, struct section *sect,
					const char *text_start)
{
	int			i;
	int			j;

	i = -1;
	j = 0;
	while (++i < (int)sect->size)
	{
		if (i % BYTE_IN_LINE_COUNT == 0)
		{
			buf[j++] = '\n';
			ft_puthex_fill_mem((uint64_t)(sect->addr + i), '0', OTOOL_PTR_LEN,
					(void*)(buf + j));
			j += OTOOL_PTR_LEN;
			buf[j++] = '\t';
		}
		ft_puthex_fill_mem((unsigned char)*(text_start + i), '0', HEX_BYTE_LEN,
				(void*)(buf + j));
		j += 2;
		buf[j++] = ' ';
	}
	buf[j] = 0;
}

/*
** output would be in the following format:
** (\nOTOOL_PTR\x20(HEX_BYTE\x20)*BYTE_IN_LINE_COUNT)
*/
static void		print_text_section(struct section *sect, const char* ptr)
{
	const char	*text_start = safe_ptr((char*)ptr + sect->offset, sect->size);
	char		*buf;

	buf = ft_strnew((sect->size / BYTE_IN_LINE_COUNT + 1)
			* (1 + OTOOL_PTR_LEN + 1) + sect->size * (HEX_BYTE_LEN + 1));
	if (!buf)
		return (ft_putstr_fd("ft_otool: failed to allocate output buf\n", 2));
	if (!text_start)
		return (ft_putstr_fd("ft_otool: section > file size\n", 2));
	prepare_buffer(buf, sect, text_start);
	ft_putendl(buf);
	ft_memdel((void**)&buf);
}

void		otool_print_text_section_32(struct segment_command *seg,
				const char *ptr)
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
		if (!ft_strncmp(sect->sectname, "__text", sizeof("__text")))
		{
			print_text_section(sect, ptr);
			break ;
		}
	}
}
