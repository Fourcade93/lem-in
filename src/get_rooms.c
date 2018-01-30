/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:40:20 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/30 16:52:32 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*create_room(char **arr, char *tag)
{
	t_room *room;

	room = (t_room *)malloc(sizeof(t_room));
	room->name = arr[0];
	if (tag)
		room->tag = ft_strdup(tag);
	else
		room->tag = NULL;
	room->x = ft_atoi(arr[1]);
	room->y = ft_atoi(arr[2]);
	room->weight = 0;
	room->connect = NULL;
	room->next = NULL;
	return (room);
}

int		check_duplicate_room(t_room *rooms, t_room *room)
{
	while (rooms)
	{
		if (ft_strequ(rooms->name, room->name))
			return (0);
		if (rooms->x == room->x && rooms->y == room->y)
			return (0);
		rooms = rooms->next;
	}
	return (1);
}

void	init_room(t_main *main, t_room **rooms, char *line, char *tag)
{
	char	**arr;
	t_room	*room;

	arr = ft_strsplit(line, ' ');
	if (!arrlen(arr, 3) || !ft_strchr(line, ' ') ||
		!ft_strchr(ft_strchr(line, ' ') + 1, ' ') ||
		ft_strchr(ft_strchr(ft_strchr(line, ' ') + 1, ' ') + 1, ' '))
		error_mngr("ERROR! Invalid room!\n", NULL);
	if (!only_digit(arr[1]) || !only_digit(arr[2]))
		error_mngr("ERROR! Invalid room coordinate!\n", NULL);
	room = create_room(arr, tag);
	ft_strdel(&(arr[1]));
	ft_strdel(&(arr[2]));
	free(arr);
	if (!check_duplicate_room(*rooms, room))
		error_mngr("ERROR! Duplicate room or room coordinate!\n", room);
	room->next = *rooms;
	*rooms = room;
	if (ft_strequ(START, tag))
		(*main).start = *rooms;
	if (ft_strequ(END, tag))
		(*main).end = *rooms;
}

void	get_start_end(t_main *main, t_room **rooms, char *cur)
{
	char *line;

	if (ft_strequ(START, cur) && (*main).start)
		error_mngr("ERROR! Duplicate start!\n", NULL);
	if (ft_strequ(END, cur) && (*main).end)
		error_mngr("ERROR! Duplicate end!\n", NULL);
	while (get_next_line(0, &line))
	{
		ft_list_pushback(&((*main).out), ft_lstnew(line, ft_strlen(line) + 1));
		if (*line == ' ' || *line == '-' || *line == 'L')
			error_mngr("ERROR! Invalid room name!\n", NULL);
		else if (ft_strequ(START, line) || ft_strequ(END, line) ||
				(*line != '#' && ft_strchr(line, '-')))
			error_mngr("ERROR input start or end!\n", NULL);
		else if (*line != '#')
		{
			init_room(&(*main), &(*rooms), line, cur);
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
	}
}

char	*get_rooms(t_main *main, t_room **rooms)
{
	char *line;

	while (get_next_line(0, &line))
	{
		ft_list_pushback(&((*main).out), ft_lstnew(line, ft_strlen(line) + 1));
		if (*line == ' ' || *line == '-' || *line == 'L')
			error_mngr("ERROR! Invalid room name!\n", NULL);
		else if (ft_strequ(START, line) || ft_strequ(END, line))
			get_start_end(&(*main), &(*rooms), line);
		else if (*line != '#' && ft_strchr(line, '-'))
			return (line);
		else if (*line != '#')
			init_room(&(*main), &(*rooms), line, NULL);
		ft_strdel(&line);
	}
	error_mngr("ERROR! Rooms connect are missing!\n", *rooms);
	return (line);
}
