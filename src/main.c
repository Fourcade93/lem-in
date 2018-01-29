/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 12:20:18 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/29 20:06:42 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void print_rooms(t_room *rooms) //delete_me
{
	t_list *tmp;
	while (rooms)
	{
		ft_printf("name: %s %d %d\n", rooms->name, rooms->x, rooms->y);
		ft_printf("weight: %d\n", rooms->weight);
		tmp = rooms->connect;
		// while (tmp)
		// {
		// 	ft_printf("connect: %s %d %d\n", ((t_room *)(tmp->content))->name, ((t_room *)(tmp->content))->x, ((t_room *)(tmp->content))->y);
		// 	tmp = tmp->next;
		// }
		ft_printf("\n");
		rooms = rooms->next;
	}
}

void print_ways(t_main main) //delete_me
{
	t_dlist *tmp;

	tmp = main.ways[0];
	while (tmp)
	{
		ft_printf("room: %s\n", tmp->data);
		tmp = tmp->next;
	}
}

int		main(void)
{
	t_main	main;
	t_room	*rooms;

	main.start = NULL;
	main.end = NULL;
	main.out = NULL;
	rooms = NULL;
	read_input(&main, &rooms);
	get_ways(main, rooms);
	// print_rooms(rooms);
	print_ways(main);
	// t_list	*tmp = main.end->connect;
	// while (tmp)
	// {
	// 	ft_printf("len: %zu\n", tmp->content_size);
	// 	tmp = tmp->next;
	// }
	// send_ants(main);
	return (0);
}
