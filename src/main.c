/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:23:40 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/05 20:09:40 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_ways(t_dlist **ways)//delete_me
{
	int		i;
	t_dlist	*tmp;

	i = -1;
	while (ways[++i])
	{
		tmp = ways[i];
		ft_printf("\nNew_way: %d\n", i);
		while (tmp)
		{
			ft_printf("%s\n", tmp->data);
			tmp = tmp->next;
		}
	}
}

void	print_rooms(t_list *rooms)
{
	t_list	*tmp;

	ft_printf("Rooms:\n");
	while (rooms)
	{
		ft_printf("%s\n", (*((t_room*)rooms->content)).name);
		tmp = (t_list*)(*((t_room*)rooms->content)).connect;
		while (tmp)
		{
			ft_printf("connect: %s\n", (*((t_room*)(((t_list*)(tmp->content))->content))).name);
			tmp = tmp->next;
		}
		rooms = rooms->next;
	}
	ft_printf("\n");
}

t_list	*read_input(int *ants_num, t_list **list)
{
	char	*line;

	*list = NULL;
	while (get_next_line(0, &line))
	{
		ft_list_pushback(&(*list), ft_lstnew(line, ft_strlen(line) + 1));
		ft_memdel((void**)(&line));
	}
	return (valid_input(*list, &(*ants_num)));
}

void	ways_to_null(t_dlist **ways, int num)
{
	int		i;

	i = num;
	while (i >= 0)
		ways[i--] = NULL;
}

void	del_ways(t_dlist **ways)
{
	int		i;
	
	i = -1;
	while (ways[++i])
		ft_dlstdel(&(ways[i]), &ft_del_content);
	free(ways);
}

int		main(void)
{
	t_list	*rooms;
	t_list	*input;
	t_dlist	**ways;
	int		ways_num;
	int		ants_num;

	rooms = read_input(&ants_num, &input);
	// print_rooms(rooms);//delete_me
	ways_num = check_ways_num(rooms);
	ways = (t_dlist**)malloc(sizeof(t_dlist*) * (ways_num + 1));
	ways_to_null(ways, ways_num);
	call_find_way(rooms, ways, ways_num);
	call_send_ants(ways, ants_num, input);
	del_ways(ways);
	ft_lstdel(&rooms, &delone_room);
	ft_lstdel(&input, &ft_del_content);
	return (0);
}
