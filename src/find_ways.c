/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 18:55:44 by fmallaba          #+#    #+#             */
/*   Updated: 2017/12/31 18:56:12 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_way_room(t_list **ways, int num, int count, char *name)
{
	int	i;
	int	j;

	i = -1;
	while (++i < num)
	{
		j = -1;
		while (++j < count && ways[i])
			ways[i] = (ways[i])->next;
		if (j == count && ways[i] && ft_strequ((ways[i])->content, name))
			return (1);
	}
	return (0);
}

void	check_short_way(t_list **ways, int num)
{
	int		max;
	int		i;

	max = 0;
	i = 0;
	while (++i < num)
		if (ft_lstlen(ways[max]) < ft_lstlen(ways[i]))
			max = i;
	if (ft_lstlen(ways[num]) <= ft_lstlen(ways[max]))
	{
		ft_lstdel(&(ways[num]), &ft_del_content);
		return ;
	}
	ft_lstdel(&(ways[max]), &ft_del_content);
	ways[max] = ways[num];
	ways[num] = NULL;
}

int		find_way_help(t_list *connect, t_list **ways, int num[2], int count)
{
	t_room	tmp;
	t_list	*buf;

	while (connect)
	{
		tmp = *((t_room*)(((t_list*)(connect->content))->content));
		buf = (*((t_room*)(((t_list*)(connect->content))->content))).connect;
		if (!ft_strequ(tmp.tag, START) && !ft_strequ(tmp.tag, MARK))
		{
			(*((t_room*)(((t_list*)(connect->content))->content))).tag = ft_strdup(MARK);
			if (!check_way_room(ways, num[0], count, tmp.name) &&
			find_way(buf, ways, num, count + 1))
			{
				ft_lstadd(&(ways[num[0]]), ft_lstnew(tmp.name, ft_strlen(tmp.name)));
				if (count > 0)
					return (num[0]);
				else if (num[1] == num[0] && ways[num[1]])
					check_short_way(ways, num[1]);
			}
			ft_strdel(&(*((t_room*)(((t_list*)(connect->content))->content))).tag);
		}
		connect = connect->next;
	}
	return (0);
}

int		find_way(t_list *connect, t_list **ways, int num[2], int count)
{
	t_list	*tmp;

	if (!connect)
		return (0);
	tmp = connect;
	while (tmp)
	{
		if (ft_strequ((*((t_room*)(((t_list*)(tmp->content))->content))).tag, END))
		{
			if (ways[num[0]])
				num[0] += 1;
			ft_lstadd(&(ways[num[0]]), ft_lstnew((*((t_room*)(((t_list*)(tmp->content))->content))).name,
							ft_strlen((*((t_room*)(((t_list*)(tmp->content))->content))).name)));
			return (1);
		}
		tmp = tmp->next;
	}
	return (find_way_help(connect, &(*ways), num, count));
}

void	call_find_way(t_list *rooms, t_list **ways, int	ways_num)
{
	int		num[2];

	while (!ft_strequ((*((t_room*)rooms->content)).tag, START))
		rooms = rooms->next;
	num[0] = 0;
	num[1] = ways_num;
	find_way((t_list*)((*((t_room*)(rooms->content))).connect), ways, num, 0);
}
