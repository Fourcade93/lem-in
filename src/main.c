/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:23:40 by fmallaba          #+#    #+#             */
/*   Updated: 2017/12/30 21:19:08 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>//delete_me

int		find_way(t_list *connect, t_list **ways)
{
	t_list	*tmp;
	t_list	*tag;

	if (!connect)
		return (0);
	ft_printf("%s\n", (*((t_room*)(((t_list*)(connect->content))->content))).name);
	if (ft_strequ((*((t_room*)(((t_list*)(connect->content))->content))).tag, START) ||
	ft_strequ((*((t_room*)(((t_list*)(connect->content))->content))).tag, MARK))
		return (0);
	if (ft_strequ((*((t_room*)(((t_list*)(connect->content))->content))).tag, END))
	{
		ft_lstadd(&(*ways), ft_lstnew((*((t_room*)(((t_list*)(connect->content))->content))).name,
		ft_strlen((*((t_room*)(((t_list*)(connect->content))->content))).name)));
		return (1);
	}
	(*((t_room*)(((t_list*)(connect->content))->content))).tag = ft_strdup(MARK);
	tag = connect;
	while (connect)
	{
		tmp = (*((t_room*)(((t_list*)(connect->content))->content))).connect;
		if (find_way(connect->next, ways) || find_way(tmp, ways))
		{
			ft_lstadd(&(*ways), ft_lstnew((*((t_room*)(((t_list*)(connect->content))->content))).name,
			ft_strlen((*((t_room*)(((t_list*)(connect->content))->content))).name)));
			return (1);
		}
		connect = connect->next;
	}
	ft_strdel(&(*((t_room*)(((t_list*)(tag->content))->content))).tag);
	ft_list_del_back(&(*ways));
	return (0);
}

void	call_find_way(t_list *rooms, t_list **ways)
{
	while (!ft_strequ((*((t_room*)rooms->content)).tag, START))
		rooms = rooms->next;
	find_way((t_list*)((*((t_room*)(rooms->content))).connect), ways);
	while (*ways)
	{
		ft_printf("Room: %s\n", (char*)(*ways)->content);
		*ways = (*ways)->next;
	}
}

t_list	*read_input(void)
{
	t_list	*list;
	char	*line;

	list = NULL;
	while (get_next_line(0, &line))
		ft_list_pushback(&list, ft_lstnew(line, ft_strlen(line)));
	return (valid_input(list));
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

int		count_connections(t_list *connect)
{
	int	len;

	len = 0;
	while (connect)
	{
		len++;
		connect = connect->next;
	}
	return (len);
}

int		check_max_tunel(t_list *rooms)
{
	int		max_start;
	int		max_end;
	t_list	*tmp;

	tmp = rooms;
	while (tmp)
	{
		if (ft_strequ((*((t_room*)tmp->content)).tag, START))
			max_start = count_connections((*((t_room*)tmp->content)).connect);
		else if (ft_strequ((*((t_room*)tmp->content)).tag, END))
			max_end = count_connections((*((t_room*)tmp->content)).connect);
		tmp = tmp->next;
	}
	if (max_start < max_end)
		return (max_start);
	return (max_end);
}

int		main(void)
{
	t_list	*rooms;
	t_list	**ways;
	int		max_tunel;
	
	rooms = read_input();
	print_rooms(rooms);
	max_tunel = check_max_tunel(rooms);
	ways = (t_list**)malloc(sizeof(t_list*) * (max_tunel + 1));
	while (max_tunel >= 0)
		ways[max_tunel--] = NULL;
	call_find_way(rooms, ways);
}