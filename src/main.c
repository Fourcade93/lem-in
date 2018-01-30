/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 12:20:18 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/30 17:41:14 by fmallaba         ###   ########.fr       */
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
	int i;

	i = -1;
	while (main.ways[++i])
	{
		tmp = main.ways[i];
		ft_printf("\nNew way:\n");
		while (tmp)
		{
			ft_printf("room: %s\n", tmp->data);
			tmp = tmp->next;
		}
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
	main.ways = get_ways(main, rooms);
	call_send_ants(main.ways, main.ants, main.out);
	return (0);
}
