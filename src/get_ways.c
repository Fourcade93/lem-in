/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ways.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:49:34 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/30 16:28:36 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	data_size_to_null(t_main main)
{
	int		i;
	t_dlist	*tmp;

	i = -1;
	while (main.ways[++i])
	{
		tmp = main.ways[i];
		while (tmp)
		{
			tmp->data_size = 0;
			tmp = tmp->next;
		}
	}
}

int		find_num_of_ways(t_list *l_start, t_list *l_end)
{
	int	start;
	int	end;

	start = ft_lstlen(l_start);
	end = ft_lstlen(l_end);
	if (start < end)
		return (start);
	return (end);
}

void	ways_to_null(t_main main, int num)
{
	while (num + 1)
		main.ways[num--] = NULL;
}

t_dlist	**get_ways(t_main main, t_room *rooms)
{
	t_list	*arr;
	t_list	*connect;
	int		num;

	if (ft_lstlen(main.start->connect) == 0 ||
		ft_lstlen(main.end->connect) == 0)
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
	start_search(arr);
	num = find_num_of_ways(main.start->connect, main.end->connect);
	main.ways = (t_dlist**)ft_memalloc(sizeof(t_dlist*) * (num + 1));
	ways_to_null(main, num);
	init_ways(main, num, rooms);
	data_size_to_null(main);
	return (main.ways);
}
