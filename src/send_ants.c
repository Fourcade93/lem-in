/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 12:51:59 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/31 16:36:12 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	send_ants_help(int end[2], t_dlist **ways, int pos)
{
	t_dlist *way;

	way = ways[pos];
	ft_dlst_toend(&way);
	while (way->prev)
	{
		way = way->prev;
		if (way->data_size)
		{
			if (end[1])
				ft_printf(" ");
			ft_printf("L%d-%s", way->data_size, way->next->data);
			if (!(way->next->next))
				end[0] += 1;
			else
				way->next->data_size = way->data_size;
			way->data_size = 0;
			end[1] += 1;
		}
	}
}

void	send_ants(t_dlist **ways, int a_num, int *cur, int end[2])
{
	int i;

	i = -1;
	end[1] = 0;
	while (ways[++i])
	{
		send_ants_help(end, ways, i);
		if (*cur <= a_num)
		{
			if (end[1])
				ft_printf(" ");
			ft_printf("L%d-%s", *cur, (ways[i])->data);
			(ways[i])->data_size = *cur;
			end[1] += 1;
			*cur += 1;
		}
	}
}

void	call_send_ants(t_dlist **ways, int a_num, t_list *input)
{
	int cur;
	int end[2];

	cur = 1;
	end[0] = 0;
	ft_printf("%s\n", input->content);
	while ((input = input->next))
		ft_printf("%s\n", input->content);
	ft_printf("\n");
	if (ft_dlstlen(ways[0]) == 1)
	{
		while (end[0] < a_num)
		{
			if (end[0] > 0)
				ft_printf(" ");
			ft_printf("L%d-%s", ++(end[0]), (ways[0])->data);
		}
		ft_printf("\n");
	}
	while (end[0] < a_num)
	{
		send_ants(ways, a_num, &cur, end);
		ft_printf("\n");
	}
}
