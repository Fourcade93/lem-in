/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ways.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:17:29 by fmallaba          #+#    #+#             */
/*   Updated: 2018/02/05 19:59:02 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_len_way(t_dlist **ways, int i)
{
	int	min;
	int	cur;

	min = ft_dlstlen(ways[0]);
	cur = ft_dlstlen(ways[i]);
	if (cur - min > min / 2)
	{
		ft_dlstdel(&(ways[i]), ft_del_content);
		return (0);
	}
	return (1);
}

int		check_ways(t_dlist **ways, int i)
{
	int		j;
	t_dlist	*tmp;
	t_dlist	*tmp2;

	if (!(tmp = ways[i]) || !check_len_way(ways, i))
		return (0);
	while (tmp->next)
	{
		j = -1;
		while (++j < i)
		{
			tmp2 = ways[j];
			while (tmp2->next)
			{
				if (ft_strequ(tmp->data, tmp2->data))
				{
					ft_dlstdel(&(ways[i]), ft_del_content);
					return (0);
				}
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
