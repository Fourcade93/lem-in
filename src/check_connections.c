/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_connections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:15:19 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/09 13:22:18 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_dif_connect(t_list *buf, char *name)
{
	char	*name2;

	while (buf)
	{
		name2 = (*((t_room*)(((t_list*)(buf->content))->content))).name;
		if (ft_strequ(name, name2))
			return (0);
		buf = buf->next;
	}
	return (1);
}

int		add_connect_help(t_list *rooms, char *str, t_list *tmp)
{
	t_list	*buf;

	while (rooms)
	{
		if (ft_strequ(str, (*((t_room*)rooms->content)).name))
			break ;
		rooms = rooms->next;
	}
	if (!rooms || ft_strlen(str) !=
	ft_strlen((*((t_room*)rooms->content)).name))
		return (0);
	buf = (*((t_room*)tmp->content)).connect;
	if (check_dif_connect(buf, (*((t_room*)(rooms->content))).name))
		ft_list_pushback(&buf, ft_lstnew(rooms, sizeof(t_list)));
	(*((t_room*)tmp->content)).connect = buf;
	buf = (*((t_room*)rooms->content)).connect;
	if (check_dif_connect(buf, (*((t_room*)(tmp->content))).name))
		ft_list_pushback(&buf, ft_lstnew(tmp, sizeof(t_list)));
	(*((t_room*)rooms->content)).connect = buf;
	return (1);
}

int		add_connect(t_list *rooms, char *str)
{
	t_list	*tmp;
	int		len;

	tmp = rooms;
	if (!ft_strchr(str, '-'))
		return (0);
	len = ft_strchr(str, '-') - str;
	while (tmp)
	{
		if ((int)ft_strlen(((*(t_room*)tmp->content)).name) == len &&
		!ft_strncmp(str, ((*(t_room*)tmp->content)).name, len))
			break ;
		tmp = tmp->next;
	}
	if (!tmp || *(str + ft_strlen(((*(t_room*)tmp->content)).name)) != '-')
		return (0);
	str = ft_strchr(str, '-');
	if (ft_strequ((*(t_room*)tmp->content).name, str + 1) ||
	!add_connect_help(rooms, ++str, tmp))
		return (0);
	return (1);
}

int		check_connections(t_list *rooms, t_list *list)
{
	while (list)
	{
		if (((char*)list->content)[0] != '#')
			if (!add_connect(rooms, list->content))
				return (0);
		list = list->next;
	}
	return (1);
}
