/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:45:49 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/20 15:47:17 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "print.h"

void		*vector_get(t_vector *v, size_t i)
{
	if (i >= v->size)
	{
		ft_putstr_fd(__func__, 2);
		ft_putstr_fd(": access to uninitialized item: ", 2);
		ft_putnbr_fd((int)i, 2);
		ft_putchar_fd('\n', 2);
		return (NULL);
	}
	return (v->elems + i * v->elem_size);
}
