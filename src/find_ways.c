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

void	find_way_help(t_list *connect, t_dlist **ways, int num[4], int count)
{
	t_room	*tmp;

	while (connect)
	{
		tmp = (t_room*)(((t_list*)(connect->content))->content);
		if (!(*tmp).tag)
		{
			(*tmp).tag = ft_strdup(MARK);
			ft_dlst_pushback(&(ways[num[0]]), ft_dlstnew((*tmp).name,
					ft_strlen((*tmp).name)));
			num[2] += 1;
			find_way((*tmp).connect, ways, num, count + 1);
			ft_dlstdel_back(&(ways[num[0]]), ft_del_content);
			ft_strdel(&(*tmp).tag);
		}
		connect = connect->next;
	}
	if (count == 0)
		ft_dlstdel(&(ways[num[1]]), &ft_del_content);
}

void	find_way(t_list *connect, t_dlist **ways, int num[4], int count)
{
	t_list	*tmp;
	t_room	*buf;

	if (!connect || check_infin(num, count))
		return ;
	tmp = connect;
	while (tmp)
	{
		buf = ((t_room*)(((t_list*)(tmp->content))->content));
		if ((*buf).tag && ft_strequ((*buf).tag, END))
		{
			ft_dlst_pushback(&(ways[num[0]]), ft_dlstnew((*buf).name,
							ft_strlen((*buf).name) + 1));
			check_ways(ways, num);
			if (count > 0)
				ft_dlstdel_back(&(ways[num[0]]), &ft_del_content);
			return ;
		}
		tmp = tmp->next;
	}
	find_way_help(connect, ways, num, count);
}

void	call_find_way(t_list *rooms, t_dlist **ways, int ways_num)
{
	int		num[4];
	t_list	*rooms2;

	rooms2 = rooms;
	while (!ft_strequ((*((t_room*)rooms->content)).tag, START))
		rooms = rooms->next;
	num[0] = 0;
	num[1] = ways_num;
	num[2] = 0;
	num[3] = 500;
	find_way((t_list*)((*((t_room*)(rooms->content))).connect), ways, num, 0);
	check_valid_ways(ways, rooms2);
}
