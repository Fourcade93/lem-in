/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:23:40 by fmallaba          #+#    #+#             */
/*   Updated: 2017/12/31 19:08:03 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>//delete_me

t_list	*read_input(int *ants_num)
{
	t_list	*list;
	char	*line;

	list = NULL;
	while (get_next_line(0, &line))
	{
		ft_list_pushback(&list, ft_lstnew(line, ft_strlen(line) + 1));
		ft_memdel((void**)(&line));
	}
	return (valid_input(list, &(*ants_num)));
}

void	print_rooms(t_list *rooms)
{
	t_list	*tmp;

	while (rooms)
	{
		ft_printf("\nName: %s\n", (*((t_room*)rooms->content)).name);
		// ft_printf("	Tag: %s", (*((t_room*)rooms->content)).tag);
		// ft_printf("	x: %d", (*((t_room*)rooms->content)).x);
		// ft_printf("	y: %d\n", (*((t_room*)rooms->content)).y);
		tmp = (t_list*)((*((t_room*)rooms->content)).connect);
		while (tmp)
		{
			ft_printf("Connect: %s\n", (*((t_room*)(((t_list*)(tmp->content))->content))).name);
			tmp = tmp->next;
		}
		rooms = rooms->next;
	}
}

void	print_ways(t_list **ways)
{
	int	i;

	i = -1;
	while (ways[++i])
	{
		ft_printf("\nNew way:\n");
		while (ways[i])
		{
			ft_printf("Room: %s\n", (ways[i])->content);
			ways[i] = (ways[i])->next;
		}
	}
}

// void	send_ants(t_list **ways, int a_num)
// {

// }

int		main(void)
{
	t_list	*rooms;
	t_list	**ways;
	int		ways_num;
	int		i;
	int		ants_num;
	
	rooms = read_input(&ants_num);
	// print_rooms(rooms);
	ways_num = check_ways_num(rooms);
	ways = (t_list**)malloc(sizeof(t_list*) * (ways_num + 1));
	i = ways_num;
	while (i >= 0)
		ways[i--] = NULL;
	call_find_way(rooms, ways, ways_num);
	print_ways(ways);
	// send_ants(ways, ants_num);
	return (0);
}