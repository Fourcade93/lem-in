/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:12:23 by fmallaba          #+#    #+#             */
/*   Updated: 2017/12/31 17:21:37 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		only_digit(char *str)
{
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int		check_start_end(t_list *list)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (list)
	{
		if (ft_strequ(list->content, START))
		{
			start++;
			if (!check_room(list->next->content, NULL))
				return (0);
		}
		if (ft_strequ(list->content, END))
		{
			end++;
			if (!check_room(list->next->content, NULL))
				return (0);
		}
		list = list->next;
	}
	if (start == 1 && end == 1)
		return (1);
	return (0);
}

t_list	*valid_input(t_list *list, int *ants_num)
{
	t_list	*rooms;
	t_list	*tmp;

	rooms = NULL;
	tmp = list;
	if (((char*)list->content)[0] == '\0' || !only_digit(list->content))
		error_mngr(1, tmp, rooms);
	*ants_num = ft_atoi(list->content);
	list = list->next;
	if (!list || !check_start_end(list))
		error_mngr(2, tmp, rooms);
	if (!list || !(rooms = check_all_rooms(&list, rooms)))
		error_mngr(3, tmp, rooms);
	if (!list || !check_connections(rooms, list))
		error_mngr(4, tmp, rooms);
	ft_lstdel(&tmp, &ft_del_content);
	return (rooms);
}
