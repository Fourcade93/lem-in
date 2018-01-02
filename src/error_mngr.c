/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mngr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:15:56 by fmallaba          #+#    #+#             */
/*   Updated: 2017/12/29 14:16:28 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	delone_room(void *content, size_t size)
{
	t_room	*room;

	room = (t_room*)content;
	ft_strdel(&((*room).name));
	ft_strdel(&((*room).tag));
	ft_lstdel(&((*room).connect), &ft_del_content);
	free(content);
	size = 0;
}

void	error_mngr(int error, t_list *list, t_list *rooms)
{
	if (error == 1)
		ft_printf(ER_NUM_ANTS);
	if (error == 2)
		ft_printf(ER_START_END);
	if (error == 3)
		ft_printf(ER_ROOM);
	if (error == 4)
		ft_printf(ER_ROOM_CONNECTS);
	if (error == 5)
		ft_printf(ER_WAY);
	ft_lstdel(&list, &ft_del_content);
	ft_lstdel(&rooms, &delone_room);
	exit(-1);
}
