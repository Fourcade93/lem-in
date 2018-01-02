/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 14:43:58 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/02 14:44:00 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	send_ants_help(t_dlist *way, int *end, int *check)
{
	ft_dlst_toend(&way);
	while (way->prev)
	{
		way = way->prev;
		if (way->data_size)
		{
			if (*check)
				ft_printf(" ");
			ft_printf("L%d-%s", way->data_size, way->next->data);
			if (!(way->next->next))
				*end += 1;
			else
				way->next->data_size = way->data_size;
			way->data_size = 0;
			*check += 1;
		}
	}
}

void	send_ants(t_dlist **ways, int a_num, int *cur, int *end)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (ways[++i])
	{
		send_ants_help(ways[i], &(*end), &check);
		if (*cur <= a_num)
		{
			if (check)
				ft_printf(" ");
			ft_printf("L%d-%s", *cur, (ways[i])->data);
			(ways[i])->data_size = *cur;
			check++;
			*cur += 1;
		}
	}
}

void	call_send_ants(t_dlist **ways, int a_num)
{
	int	cur;
	int	end;

	cur = 1;
	end = 0;
	while (end < a_num)
	{
		send_ants(ways, a_num, &cur, &end);
		ft_printf("\n");
	}
}
