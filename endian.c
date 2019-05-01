#include <stdint.h>

uint32_t	be2le(uint32_t i)
{
	return ((((i & (0xff << 0))) << 16) |
			(((i & (0xff << 8))) << 8) |
			(((i & (0xff << 16))) >> 8) |
			(((i & (0xff << 24))) >> 24));
}

uint64_t	be2le64(uint64_t in_num)
{
	unsigned char		*in;
	unsigned char		*out;
	uint64_t			out_num;
	int					i;

	in = (unsigned char*)&in_num;
	out = (unsigned char*)&out_num;
	i = -1;
	while (++i < 8)
	{
		out[i] = in[8 - 1 - i];
	}
	return (out_num);
}
