/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_connects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:47:30 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/29 18:08:42 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*check_room_exist(t_room *rooms, char *room)
{
	t_room *tmp;

	tmp = rooms;
	while (tmp && !ft_strequ(room, tmp->name))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp);
}

int		add_connect(t_room *rooms, char *line)
{
	char **arr;
	t_room *first;
	t_room *second;

	arr = ft_strsplit(line, '-');
	if (!arrlen(arr, 2) || !ft_strchr(line, '-') ||
		ft_strchr(ft_strchr(line, '-') + 1, '-'))
		return (ft_printf("ERROR! Invalid room connect!\n"));
	first = check_room_exist(rooms, arr[0]);
	second = check_room_exist(rooms, arr[1]);
	ft_strdel(&(arr[0]));
	ft_strdel(&(arr[1]));
	free(arr);
	if (!first || !second)
		return (ft_printf("ERROR! Connect with non exist room!\n"));
	ft_lstadd(&(first->connect), ft_lstnew(NULL, 0));
	first->connect->content = second;
	ft_lstadd(&(second->connect), ft_lstnew(NULL, 0));
	second->connect->content = first;
	return (0);
}

void	get_connects(t_main main, t_room *rooms, char *line)
{
	if (*line != '#' && add_connect(rooms, line))
	{
		ft_strdel(&line);
		return ;
	}
	while (get_next_line(0, &line))
	{
		ft_list_pushback(&(main.out), ft_lstnew(line, ft_strlen(line) + 1));
		if (ft_strequ(START, line) || ft_strequ(END, line))
		{
			ft_printf("ERROR!\n");
			ft_strdel(&line);
			break;
		}
		if (*line != '#' && add_connect(rooms, line))
			break;
		ft_strdel(&line);
	}
}
