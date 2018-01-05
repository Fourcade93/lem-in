/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 18:55:44 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/05 14:16:22 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_way_room(t_dlist **ways, int num, int count, char *name)
{
	int		i;
	int		j;
	t_dlist	*tmp;

	i = -1;
	while (++i < num)
	{
		j = -1;
		tmp = ways[i];
		while (++j < count && tmp)
			tmp = tmp->next;
		if (j == count && tmp && ft_strequ(tmp->data, name))
			return (1);
	}
	return (0);
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
	if (ft_dlstlen(ways[num]) <= ft_dlstlen(ways[max]))
	{
		ft_dlstdel(&(ways[num]), &ft_del_content);
		return ;
	}
	ft_dlstdel(&(ways[max]), &ft_del_content);
	ways[max] = ways[num];
	ways[num] = NULL;
}

int		find_way_help(t_list *connect, t_dlist **ways, int num[2], int count)
{
	t_room	*tmp;

	while (connect)
	{
		tmp = (t_room*)(((t_list*)(connect->content))->content);
		if (!ft_strequ((*tmp).tag, START) && !ft_strequ((*tmp).tag, MARK))
		{
			(*tmp).tag = ft_strdup(MARK);
			if (/*!check_way_room(ways, num[0], count, (*tmp).name) &&
			*/find_way((*tmp).connect, ways, num, count + 1))
			{
				ft_strdel(&(*tmp).tag);
				ft_dlstadd(&(ways[num[0]]), ft_dlstnew((*tmp).name,
					ft_strlen((*tmp).name) + 1));
				if (count > 0)
					return (1);
				else if (num[1] == num[0] && ways[num[1]])
					check_short_way(ways, num[1]);
			}
			ft_strdel(&(*tmp).tag);
		}
		connect = connect->next;
	}
	return (0);
}

int		find_way(t_list *connect, t_dlist **ways, int num[2], int count)
{
	t_list	*tmp;
	t_room	*buf;

	if (!connect)
		return (0);
	tmp = connect;
	while (tmp)
	{
		buf = ((t_room*)(((t_list*)(tmp->content))->content));
		if (ft_strequ((*buf).tag, END))
		{
			if (ways[num[0]])
				num[0] += 1;
			ft_dlstadd(&(ways[num[0]]), ft_dlstnew((*buf).name,
							ft_strlen((*buf).name) + 1));
			return (1);
		}
		tmp = tmp->next;
	}
	return (find_way_help(connect, &(*ways), num, count));
}

void	call_find_way(t_list *rooms, t_dlist **ways, int ways_num)
{
	int		num[2];
	int		i;
	t_dlist	*tmp;

	while (!ft_strequ((*((t_room*)rooms->content)).tag, START))
		rooms = rooms->next;
	num[0] = 0;
	num[1] = ways_num;
	find_way((t_list*)((*((t_room*)(rooms->content))).connect), ways, num, 0);
	i = -1;
	while (ways[++i])
	{
		tmp = ways[i];
		// ft_printf("\nnew way\n");
		while (tmp)
		{
			// ft_printf("%s\n", tmp->data);
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
