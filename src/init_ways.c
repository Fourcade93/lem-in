/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:23:13 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/31 15:36:23 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void delete_min(t_list **connect, t_list *min)
{
	t_list *tmp;
	t_list *buf;

	if (ft_strequ(((t_room *)((*connect)->content))->name,
				  ((t_room *)(min->content))->name))
	{
		buf = (*connect)->next;
		free(*connect);
		*connect = buf;
		return;
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
			return;
		}
		tmp = tmp->next;
	}
}

int		check_ways(t_main main, int i)
{
	int		j;
	t_dlist	*tmp;
	t_dlist	*tmp2;

	tmp = main.ways[i];
	while (tmp->next)
	{
		j = -1;
		while (++j < i)
		{
			tmp2 = main.ways[j];
			while (tmp2->next)
			{
				if (ft_strequ(tmp->data, tmp2->data))
				{
					ft_dlstdel(&(main.ways[i]), ft_del_content);
					return (0);
				}
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

void	fill_way(t_main main, t_list *min, int i)
{
	t_list	*tmp;
	t_list	*buf;
	int		weight;

	ft_dlstadd(&(main.ways[i]), ft_dlstnew(main.end->name,
							ft_strlen(main.end->name) + 1));
	ft_dlstadd(&(main.ways[i]), ft_dlstnew(((t_room *)(min->content))->name,
							ft_strlen(((t_room *)(min->content))->name) + 1));
	weight = min->content_size - 1;
	tmp = min;
	while (1)
	{
		buf = ((t_room *)(tmp->content))->connect;
		tmp = ((t_room *)(tmp->content))->connect;
		while (tmp)
		{
			if (((t_room *)(tmp->content))->weight == weight - 1 &&
				!ft_strequ(((t_room *)(tmp->content))->name, main.end->name))
				break ;
			tmp = tmp->next;
		}
		if (ft_strequ(((t_room *)(tmp->content))->name, main.start->name))
			break ;
		ft_dlstadd(&(main.ways[i]), ft_dlstnew(((t_room *)(tmp->content))->name,
								ft_strlen(((t_room *)(tmp->content))->name) + 1));
		weight--;
	}
}

t_list	*get_min_way(t_list *tmp, t_list *min)
{
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
	int		min_len;
	t_list	*max;
	t_list	*min;
	t_list	*tmp;

	i = 1;
	min_len = ft_dlstlen(main.ways[0]);
	while (i < num)
	{
		tmp = main.end->connect;
		max = tmp;
		while ((tmp = tmp->next))
			if (max->content_size < tmp->content_size)
				max = tmp;
		tmp = main.end->connect;
		min = max;
		min = get_min_way(tmp, min);
		min_len = min->content_size;
		fill_way(main, min, i);
		delete_min(&(main.end->connect), min);
		if (check_ways(main, i))
			i++;
		if (!main.end->connect)
			break ;
	}
	usleep(1000000);
}

void	init_ways(t_main main, int num, t_room *rooms)
{
	t_list *tmp;
	t_list *min;

	tmp = main.end->connect;
	min = tmp;
	while ((tmp = tmp->next))
		if (min->content_size < tmp->content_size)
			min = tmp;
	tmp = main.end->connect;
	while ((tmp = tmp->next))
		if (tmp->content_size > 0 && min->content_size > tmp->content_size)
			min = tmp;
	if (min->content_size == 0)
		error_mngr("ERROR! There is no any way!\n", rooms);
	fill_way(main, min, 0);
	delete_min(&(main.end->connect), min);
	init_other_ways(main, num);
}
