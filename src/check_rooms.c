/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:14:41 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/02 18:53:06 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list	*new_list(t_room *room)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	new->content = room;
	new->content_size = 0;
	new->next = NULL;
	return (new);
}

t_room	*create_room(char *str, char *tag)
{
	t_room	*room;
	char	*tmp;

	room = (t_room*)malloc(sizeof(t_room));
	tmp = str;
	str = ft_strchr(str, ' ');
	str++;
	(*room).name = ft_strsub(tmp, 0, str - tmp - 1);
	if (tag)
		(*room).tag = ft_strdup(tag);
	else
		(*room).tag = tag;
	(*room).x = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	str++;
	(*room).y = ft_atoi(str);
	(*room).connect = NULL;
	return (room);
}

t_room	*check_room(char *str, char *tag)
{
	char	*tmp;

	if (*str == '#' || *str == 'L')
		return (NULL);
	tmp = str;
	str = ft_strchr(str, ' ');
	if (!str || !ft_isdigit(*++str))
		return (NULL);
	while (ft_isdigit(*str))
		str++;
	if ((!*str || *str != ' ') && !ft_isdigit(*++str))
		return (NULL);
	str++;
	while (ft_isdigit(*str))
		str++;
	if (*str != '\0')
		return (NULL);
	return (create_room(tmp, tag));
}

void	check_all_rooms_help(t_list **list, t_list **rooms)
{
	t_room	*room;
	char	*tag;

	if (ft_strequ((*list)->content, START))
		tag = ft_strdup(START);
	else
		tag = ft_strdup(END);
	(*list) = (*list)->next;
	while ((*list) && *((char*)((*list)->content)) == '#')
		(*list) = (*list)->next;
	room = check_room((*list)->content, tag);
	ft_list_pushback(&(*rooms), new_list(room));
	ft_strdel(&tag);
}

t_list	*check_all_rooms(t_list **list, t_list *rooms)
{
	t_room	*room;
	t_list	*tmp;

	tmp = *list;
	while ((*list))
	{
		if (((char*)(*list)->content)[0] != '#' &&
			ft_strchr((*list)->content, '-'))
			break ;
		else if (ft_strequ((*list)->content, START) ||
					ft_strequ((*list)->content, END))
			check_all_rooms_help(&(*list), &rooms);
		else if (((char*)(*list)->content)[0] != '#' &&
					(room = check_room((*list)->content, NULL)))
			ft_list_pushback(&rooms, new_list(room));
		else if (((char*)(*list)->content)[0] != '#')
			error_mngr(3, *list, rooms);
		(*list) = (*list)->next;
	}
	if (!(*list) || !check_duplicate_room(rooms))
		error_mngr(3, tmp, rooms);
	return (rooms);
}
