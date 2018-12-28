/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_string_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 23:36:13 by vrybalko          #+#    #+#             */
/*   Updated: 2018/03/31 23:38:11 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "ft_string.h"

void			ft_del_string_array(char **lines)
{
	int		i;

	if (lines == NULL || *lines == NULL)
		return ;
	i = -1;
	while (lines[++i])
		ft_strdel(&(lines[i]));
	ft_memdel((void*)&lines);
}
