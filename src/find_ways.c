/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 18:55:44 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/09 14:45:58 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_same_room(t_dlist **ways, int num[2])
{
	int		i;
	t_dlist	*tmp;
	t_dlist	*cur;

	i = -1;
	while (++i < num[0])
	{
		tmp = ways[i];
		cur = ways[num[0]];
		if (tmp && cur)
			while (!ft_strequ(tmp->data, cur->data) && (tmp = tmp->next) &&
			(cur = cur->next))
				;
		if (cur && tmp && tmp->next &&
		ft_strequ(tmp->data, cur->data))
			return (i);
	}
	return (-1);
}

void	check_ways(t_dlist **ways, int num[2])
{
	int		same;

	if (num[0] == 0)
	{
		lstcpy(ways[0], &(ways[1]));
		num[0] += 1;
	}
	else if ((same = check_same_room(ways, num)) != -1)
	{
		if (ft_dlstlen(ways[same]) > ft_dlstlen(ways[num[0]]))
		{
			ft_dlstdel(&(ways[same]), &ft_del_content);
			lstcpy(ways[num[0]], &(ways[same]));
		}
	}
	else if (num[0] == num[1])
		check_short_way(ways, num[0]);
	else
	{
		lstcpy(ways[num[0]], &(ways[num[0] + 1]));
		num[0] += 1;
	}
}

int		find_way_help(t_list *connect, t_dlist **ways, int num[2], int count)
{
	t_room	*tmp;

	while (connect)
	{
		tmp = (t_room*)(((t_list*)(connect->content))->content);
		if (!(*tmp).tag || (!ft_strequ((*tmp).tag, START) &&
			!ft_strequ((*tmp).tag, MARK)))
		{
			(*tmp).tag = ft_strdup(MARK);
			ft_dlst_pushback(&(ways[num[0]]), ft_dlstnew((*tmp).name,
					ft_strlen((*tmp).name)));
			find_way((*tmp).connect, ways, num, count + 1);
			ft_dlstdel_back(&(ways[num[0]]), ft_del_content);
			ft_strdel(&(*tmp).tag);
		}
		connect = connect->next;
	}
	if (count == 0)
		ft_dlstdel(&(ways[num[1]]), &ft_del_content);
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
			ft_dlst_pushback(&(ways[num[0]]), ft_dlstnew((*buf).name,
							ft_strlen((*buf).name) + 1));
			check_ways(ways, num);
			ft_dlstdel_back(&(ways[num[0]]), &ft_del_content);
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
