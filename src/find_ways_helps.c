/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways_helps.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:50:03 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/09 14:50:06 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	check_short_way(t_dlist **ways, int num)
{
	int		max;
	int		i;

	max = 0;
	i = 0;
	while (++i < num)
		if (ft_dlstlen(ways[max]) < ft_dlstlen(ways[i]))
			max = i;
	if (ft_dlstlen(ways[num]) < ft_dlstlen(ways[max]))
	{
		ft_dlstdel(&(ways[max]), &ft_del_content);
		ways[max] = ways[num];
	}
}

void	lstcpy(t_dlist *src, t_dlist **dst)
{
	while (src)
	{
		ft_dlst_pushback(&(*dst), ft_dlstnew(src->data, src->data_size));
		src = src->next;
	}
}
