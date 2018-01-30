/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mngr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 13:10:35 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/30 17:41:44 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	dont_del(void *content, size_t size)
{
	(void)content;
	(void)size;
}

void	del_rooms(t_room *rooms)
{
	t_room	*buf;

	if (!rooms)
		return ;
	while (rooms)
	{
		buf = rooms->next;
		ft_strdel(&(rooms->name));
		ft_strdel(&(rooms->tag));
		ft_lstdel(&(rooms->connect), dont_del);
		free(rooms);
		rooms = buf;
	}
}

void	error_mngr(char *error, t_room *rooms)
{
	// (void)error;
	del_rooms(rooms);
	// ft_printf("ERROR\n");
	ft_printf(error);
	exit(-1);
}
