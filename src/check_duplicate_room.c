/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicate_room.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 14:44:34 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/02 18:53:26 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_if_duplicate(t_room room, t_list *rooms)
{
	while (rooms)
	{
		if (ft_strequ(room.name, (*((t_room*)rooms->content)).name) ||
			(room.x == (*((t_room*)(rooms->content))).x &&
			room.y == (*((t_room*)rooms->content)).y))
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
