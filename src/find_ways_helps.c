/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways_helps.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:50:03 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/11 15:51:41 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lstcpy(t_dlist *src, t_dlist **dst)
{
	while (src)
	{
		ft_dlst_pushback(&(*dst), ft_dlstnew(src->data, src->data_size));
		src = src->next;
	}
}

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
		lstcpy(ways[num], &(ways[max]));
	}
}

int		check_infin(int num[4], int count)
{
	if (num[2] > 5000 && count > num[3])
		return (1);
	else if (num[2] > 5000 && count == num[3])
	{
		num[2] = 0;
		(num[3] > 1) ? num[3] -= 1 : num[3];
	}
	else if (num[2] > 5000 && count < num[3])
		num[3] = (count > 4) ? count - count / 5 : 1;
	return (0);
}

void	check_ways_len(t_dlist **ways)
{
	int		i;
	int		j;
	t_dlist	*tmp;

	i = -1;
	while (ways[++i])
	{
		j = i;
		while (ways[++j])
			if (ft_dlstlen(ways[i]) > ft_dlstlen(ways[j]))
			{
				tmp = ways[i];
				ways[i] = ways[j];
				ways[j] = tmp;
			}
	}
	if (i == 0)
		return ;
	i = 0;
	while (ways[++i])
		if (ft_dlstlen(ways[0]) <= ft_dlstlen(ways[i]) / 2)
			ft_dlstdel(&(ways[i]), &ft_del_content);
}

void	check_valid_ways(t_dlist **ways, t_list *rooms)
{
	int		i;
	t_dlist	*tmp;

	check_ways_len(ways);
	i = -1;
	while (ways[++i])
	{
		tmp = ways[i];
		while (tmp)
		{
			tmp->data_size = 0;
			tmp = tmp->next;
		}
	}
	if (i == 0)
	{
		free(ways);
		error_mngr(5, NULL, rooms);
	}
}
