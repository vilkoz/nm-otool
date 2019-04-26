#include "print.h"
#include "ft_string.h"

void	ft_puthex(unsigned long long n)
{
	static const char	chars[] = "0123456789abcdef";
	char				buf[sizeof(unsigned long long) * 8 + 1];
	int					i;
	unsigned long long	copy;

	copy = n;
	i = -1;
	while (copy > 0)
	{
		copy >>= 4;
		i++;
	}
	buf[i + 1] = 0;
	while (n > 0)
	{
		buf[i] = chars[n & 0xF];
		i--;
		n >>= 4;
	}
	ft_putstr(&(buf[0]));
}

void	ft_puthex_fill(unsigned long long n, char fill_char, unsigned int width)
{
	unsigned long long	copy;
	int					size;
	int					i;
	char				buf[sizeof(unsigned long long) * 8 + 1 + 2];

	copy = n;
	size = 0;
	while (copy > 0)
	{
		copy >>= 4;
		size++;
	}
	i = -1;
	while (++i < ((int)width - size))
		buf[i] = fill_char;
	buf[i] = 0;
	ft_putstr(&(buf[0]));
	ft_puthex(n);
}

void	ft_puthex_mem(unsigned long long n, void *mem)
{
	static const char	chars[] = "0123456789abcdef";
	char				buf[sizeof(unsigned long long) * 8 + 1];
	int					i;
	unsigned long long	copy;

	copy = n;
	i = -1;
	while (copy > 0)
	{
		copy >>= 4;
		i++;
	}
	buf[i + 1] = 0;
	while (n > 0)
	{
		buf[i] = chars[n & 0xF];
		i--;
		n >>= 4;
	}
	ft_strcpy(mem, (void*)&(buf[0]));
}

void	ft_puthex_fill_mem(unsigned long long n, char fill_char,
			unsigned int width, void *mem)
{
	unsigned long long	copy;
	int					size;
	int					i;
	char				buf[sizeof(unsigned long long) * 8 + 1 + 2];

	copy = n;
	size = 0;
	while (copy > 0)
	{
		copy >>= 4;
		size++;
	}
	i = -1;
	while (++i < ((int)width - size))
		buf[i] = fill_char;
	buf[i] = 0;
	ft_strcpy(mem, &(buf[0]));
	ft_puthex_mem(n, (void*)(((char*)mem) + ((int)width - size)));
}
