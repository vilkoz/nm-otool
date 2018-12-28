/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 23:37:12 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/24 17:21:48 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "memory.h"

static void		do_nothing_with_data(void *data)
{
	(void)data;
}

void			vector_delete(t_vector **v, void (*del)(void*))
{
	int		i;

	if (v == NULL || *v == NULL)
		return ;
	if (del == NULL)
		del = do_nothing_with_data;
	i = -1;
	while (++i < (int)(*v)->size)
		del(vector_get((*v), i));
	ft_memdel((void**)&((*v)->elems));
	ft_memdel((void**)v);
}
