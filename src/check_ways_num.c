/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ways_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 18:57:39 by fmallaba          #+#    #+#             */
/*   Updated: 2017/12/31 18:58:23 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

int		check_ways_num(t_list *rooms)
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
