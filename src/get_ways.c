/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ways.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:49:34 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/28 20:09:27 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	dont_del(void *content, size_t size)
{
	(void)content;
	(void)size;
}

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

void	start_search(t_main main, t_list *arr)
{
	t_list	*buf;
	t_list	*tmp;
	t_list	*connect;

	buf = NULL;
	(void)main;
	while (ft_lstlen(arr) > 0)
	{
		tmp = arr;
		while (tmp)
		{
			connect = ((t_room*)(tmp->content))->connect;
			while (connect)
			{
				if (ft_strequ(((t_room *)(connect->content))->tag, END))
					put_weight_to_end(((t_room*)(connect->content))->connect, tmp);
				else if ((((t_room *)(connect->content))->weight > ((t_room *)(tmp->content))->weight + 1 ||
						  ((t_room *)(connect->content))->weight == 0) &&
						 !ft_strequ(((t_room *)(connect->content))->tag, START))
				{
					((t_room *)(connect->content))->weight = ((t_room *)(tmp->content))->weight + 1;
					ft_lstadd(&buf, connect);
				}
				connect = connect->next;
			}
			tmp = tmp->next;
		}
		arr = buf;
	}
}

void	get_ways(t_main main)
{
	t_list	*arr;
	t_list	*connect;

	connect = main.start->connect;
	ft_printf("start: %d\n\n", ((t_room*)(main.start->connect->content))->weight);
	arr = NULL;
	while (connect)
	{
		((t_room *)(connect->content))->weight = 1;
		ft_printf("Connect: %d\n\n", ((t_room *)(connect->content))->x);
		ft_lstadd(&arr, connect);
		connect = connect->next;
	}
	start_search(main, arr);
}
