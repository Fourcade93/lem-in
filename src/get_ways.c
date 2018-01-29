/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ways.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:49:34 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/29 20:06:40 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	put_weight_to_end(t_list *connect, t_list *tmp)
{
	while (connect)
	{
		if (ft_strequ(((t_room *)(connect->content))->name, ((t_room *)(tmp->content))->name))
		{
			connect->content_size = ((t_room *)(tmp->content))->weight + 1;
			break ;
		}
		connect = connect->next;
	}
}
void print_rooms(t_room *rooms); //delete_me
void	start_search(t_main main, t_list *arr, t_room *rooms)
{
	t_list	*buf;
	t_list	*tmp;
	t_list	*connect;

	buf = NULL;
	(void)main;
	(void)rooms;
	while (ft_lstlen(arr) > 0)
	{
		tmp = arr;
		while (tmp)
		{
			// ft_printf("Name: %s\n", ((t_room *)(tmp->content))->name);
			connect = ((t_room *)(tmp->content))->connect;
			while (connect)
			{
				if (ft_strequ(((t_room *)(connect->content))->tag, END))
					put_weight_to_end(((t_room*)(connect->content))->connect, tmp);
				else if ((((t_room *)(connect->content))->weight > ((t_room *)(tmp->content))->weight + 1 ||
						  ((t_room *)(connect->content))->weight == 0) &&
						 !ft_strequ(((t_room *)(connect->content))->tag, START))
				{
					((t_room *)(connect->content))->weight = ((t_room *)(tmp->content))->weight + 1;
					ft_lstadd(&buf, ft_lstnew(NULL, 0));
					buf->content = connect->content;
				}
				connect = connect->next;
			}
			tmp = tmp->next;
		}
		ft_lstdel(&arr, dont_del);
		arr = buf;
		buf = NULL;
		// print_rooms(rooms);//delete_me
	}
}

void	init_ways(t_main main, t_room *rooms, int num)
{
	t_list	*tmp;
	t_list	*min;
	int		weight;

	(void)num;//delete_me
	(void)rooms;//delete_me
	tmp = main.end->connect;
	min = tmp;
	while ((tmp = tmp->next))
		if (min->content_size > tmp->content_size)
			min = tmp;
	ft_dlstadd(&(main.ways[0]), ft_dlstnew(main.end->name, ft_strlen(main.end->name) + 1));
	ft_dlstadd(&(main.ways[0]), ft_dlstnew(((t_room *)(min->content))->name,
										   ft_strlen(((t_room *)(min->content))->name) + 1));
	weight = min->content_size - 1;
	tmp = min;
	while (1)
	{
		tmp = ((t_room*)(tmp->content))->connect;
		while (tmp)
		{
			if (((t_room*)(tmp->content))->weight == weight - 1)
				break ;
			tmp = tmp->next;
		}
		if (ft_strequ(((t_room*)(tmp->content))->name, main.start->name))
			break ;
		ft_dlstadd(&(main.ways[0]), ft_dlstnew(((t_room *)(tmp->content))->name,
					ft_strlen(((t_room *)(tmp->content))->name) + 1));
		weight--;
	}
}

int		find_num_of_ways(t_main main)
{
	int	start;
	int	end;

	start = ft_lstlen(main.start->connect);
	end = ft_lstlen(main.end->connect);
	if (start < end)
		return (start);
	return (end);
}

void	ways_to_null(t_main main, int num)
{
	while (num + 1)
		main.ways[num--] = NULL;
}

void	get_ways(t_main main, t_room *rooms)
{
	t_list	*arr;
	t_list	*connect;
	int		num;
	
	if (ft_lstlen(main.start->connect) == 0 || ft_lstlen(main.end->connect) == 0)
		error_mngr("ERROR! Start or end has no connections!\n", rooms);
	connect = main.start->connect;
	arr = NULL;
	while (connect)
	{
		((t_room *)(connect->content))->weight = 1;
		ft_lstadd(&arr, ft_lstnew(NULL, 0));
		arr->content = connect->content;
		connect = connect->next;
	}
	start_search(main, arr, rooms);
	num = find_num_of_ways(main);
	main.ways = (t_dlist**)ft_memalloc(sizeof(t_dlist*) * (num + 1));
	ways_to_null(main, num);
	init_ways(main, rooms, num);
}
