/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:01:01 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/20 15:11:01 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "memory.h"
#include "print.h"

void		vector_set(t_vector *v, size_t i, void *data)
{
	if (i >= v->size)
	{
		ft_putstr_fd(__func__, 2);
		ft_putstr_fd(": access to uninitialized item: ", 2);
		ft_putnbr_fd((int)i, 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
	ft_memcpy((v->elems + i * v->elem_size), data, v->elem_size);
}
