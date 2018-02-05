/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 12:20:18 by fmallaba          #+#    #+#             */
/*   Updated: 2018/02/05 19:59:12 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_ways(t_dlist **ways)//delete_me
{
	int	i = -1;

	while (ways[++i])
	{
		t_dlist	*tmp = ways[i];
		ft_printf("\nWay number %d:\n", i);
		while (tmp)
		{
			ft_printf("%s\n", tmp->data);
			tmp = tmp->next;
		}
	}
}

int		check_shortest_way(t_main main)
{
	t_list	*tmp;

	tmp = main.start->connect;
	while (tmp)
	{
		if (ft_strequ(((t_room*)(tmp->content))->tag, END))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		main(void)
{
	t_main	main;
	t_room	*rooms;

	main.start = NULL;
	main.end = NULL;
	main.out = NULL;
	main.mark = ft_strdup("mark");
	rooms = NULL;
	read_input(&main, &rooms);
	if (!check_shortest_way(main))
		main.ways = get_ways(main, rooms);
	else
	{
		main.ways = (t_dlist**)ft_memalloc(sizeof(t_dlist*) * 2);
		main.ways[1] = NULL;
		main.ways[0] = NULL;
		ft_dlstadd(&(main.ways[0]), ft_dlstnew(main.end->name,
								ft_strlen(main.end->name) + 1));
	}
	call_send_ants(main.ways, main.ants, main.out);
	return (0);
}
