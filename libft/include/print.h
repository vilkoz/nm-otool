/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 15:11:32 by vrybalko          #+#    #+#             */
/*   Updated: 2019/04/26 11:01:20 by vitalii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int				n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_print_array(char **arr);
void				ft_puthex(unsigned long long n);
void				ft_puthex_fill(unsigned long long n, char fill_char,
						unsigned int width);
void				ft_puthex_mem(unsigned long long n, void *mem);
void				ft_puthex_fill_mem(unsigned long long n, char fill_char,
						unsigned int width, void *mem);

#endif
