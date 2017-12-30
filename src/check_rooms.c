/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:14:41 by fmallaba          #+#    #+#             */
/*   Updated: 2017/12/29 14:49:25 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*check_room(char *str, char *tag)
{
	t_room	*room;
	char	*tmp;

	room = (t_room*)malloc(sizeof(t_room));
	if (*str == '#' || *str == 'L')
		return (NULL);
	tmp = str;
	str = ft_strchr(str, ' ');
	if (!str || !ft_isdigit(*++str))
		return (NULL);
	(*room).name = ft_strsub(tmp, 0, str - tmp - 1);
	if (tag)
		(*room).tag = ft_strdup(tag);
	else
		(*room).tag = tag;
	(*room).x = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	if ((!*str || *str != ' ') && !ft_isdigit(*++str))
		return (NULL);
	str++;
	(*room).y = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	if (*str != '\0')
		return (NULL);
	(*room).connect = NULL;
	return (room);
}

int		check_if_duplicate(t_room room, t_list *rooms)
{
	while (rooms)
	{
		if (ft_strequ(room.name, (*((t_room*)rooms->content)).name) ||
	(room.x == (*((t_room*)(rooms->content))).x && room.y == (*((t_room*)rooms->content)).y))
			return (1);
		rooms = rooms->next;
	}
	return (0);
}

int		check_duplicate_room(t_list *rooms)
{
	while (rooms && rooms->next)
	{
		if (check_if_duplicate(*(t_room*)rooms->content, rooms->next))
			return (0);
		rooms = rooms->next;
	}
	return (1);
}

t_list	*check_all_rooms(t_list **list, t_list *rooms)
{
	t_list	*tmp;
	t_room	*room;

	tmp = *list;
	while (tmp)
	{
		if (((char*)tmp->content)[0] == 'L')
			error_mngr(3, *list, rooms);
		else if (((char*)tmp->content)[0] != '#' && ft_strchr(tmp->content, '-'))
			break ;
		else if (ft_strequ(tmp->content, START) && (room = check_room(tmp->next->content, START)))
		{
			tmp = tmp->next;
			ft_list_pushback(&rooms, ft_lstnew(room, sizeof(t_room)));
		}
		else if (ft_strequ(tmp->content, END) && (room = check_room(tmp->next->content, END)))
		{
			tmp = tmp->next;
			ft_list_pushback(&rooms, ft_lstnew(room, sizeof(t_room)));
		}
		else if (((char*)tmp->content)[0] != '#' && (room = check_room(tmp->content, NULL)))
			ft_list_pushback(&rooms, ft_lstnew(room, sizeof(t_room)));
		else if (((char*)tmp->content)[0] != '#')
			error_mngr(3, *list, rooms);
		tmp = tmp->next;
	}
	if (!tmp || !check_duplicate_room(rooms))
		error_mngr(3, *list, rooms);
	*list = tmp;
	return (rooms);
}
