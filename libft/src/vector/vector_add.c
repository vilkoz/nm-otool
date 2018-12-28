/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:38:43 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/08 22:05:50 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "memory.h"

void		vector_set_ready(t_vector *v)
{
	v->ready = 1;
	if (v->allocated_size != v->size)
	{
		v->elems = ft_realloc(v->elems, v->elem_size * v->size,
				v->elem_size * v->size);
		v->allocated_size = v->size;
	}
}

void		vector_add(t_vector *v, void *elem)
{
	if (v == NULL || elem == NULL)
		return ;
	if (v->allocated_size < v->size + 1)
	{
		v->elems = ft_realloc(v->elems, v->elem_size * v->size,
				v->elem_size * (v->size * 2));
		v->allocated_size += v->size;
	}
	ft_memcpy(v->elems + v->size * v->elem_size, elem, v->elem_size);
	v->size += 1;
}
