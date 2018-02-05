/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:23:13 by fmallaba          #+#    #+#             */
/*   Updated: 2018/02/05 19:58:19 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	delete_elem(t_list **connect, t_list *min)
{
	t_list *tmp;
	t_list *buf;

	if (ft_strequ(((t_room *)((*connect)->content))->name,
		((t_room *)(min->content))->name))
	{
		buf = (*connect)->next;
		free(*connect);
		*connect = buf;
		return ;
	}
	tmp = *connect;
	while (tmp->next)
	{
		if (ft_strequ(((t_room *)(tmp->next->content))->name,
					((t_room *)(min->content))->name))
		{
			buf = tmp->next->next;
			free(tmp->next);
			tmp->next = buf;
			return ;
		}
		tmp = tmp->next;
	}
}

t_list	*get_min_way(t_list *tmp, t_list *min)
{
	min = tmp;
	while (tmp)
	{
		if (tmp->content_size < min->content_size)
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

void	init_other_ways(t_main main, int num)
{
	int		i;
	t_list	*max;
	t_list	*min;
	t_list	*tmp;

	i = 1;
	while (i < num)
	{
		if (!main.end->connect)
			break;
		tmp = main.end->connect;
		max = tmp;
		while (tmp && (tmp = tmp->next))
			if (max->content_size < tmp->content_size)
				max = tmp;
		tmp = main.end->connect;
		min = get_min_way(tmp, max);
		if (fill_way(main, min, i, min->content_size))
			ft_dlst_pushback(&(main.ways[i]), ft_dlstnew(main.end->name,
								ft_strlen(main.end->name) + 1));
		delete_elem(&(main.end->connect), min);
		if (check_ways(main.ways, i))
			i++;
	}
}
void	init_ways(t_main main, int num, t_room *rooms)
{
	t_list *tmp;
	t_list *min;

	tmp = main.end->connect;
	while (tmp)
	{
		if (tmp->content_size == 0)
			delete_elem(&(main.end->connect), tmp);
		else
			tmp = tmp->next;
	}
	tmp = main.end->connect;
	min = tmp;
	while (tmp && (tmp = tmp->next))
		if (min->content_size > tmp->content_size)
			min = tmp;
	if (!min)
		error_mngr("ERROR! There is no any way!\n", rooms);
	if (fill_way(main, min, 0, min->content_size))
		ft_dlst_pushback(&(main.ways[0]), ft_dlstnew(main.end->name,
								ft_strlen(main.end->name) + 1));
	delete_elem(&(main.end->connect), min);
	init_other_ways(main, num);
}
