/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mngr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:15:56 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/02 16:38:29 by fmallaba         ###   ########.fr       */
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

void	error_mngr(t_list *list, t_list *rooms)
{
	ft_printf("ERROR\n");
	ft_lstdel(&list, &ft_del_content);
	ft_lstdel(&rooms, &delone_room);
	exit(-1);
}
