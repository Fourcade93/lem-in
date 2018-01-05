/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 14:43:58 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/05 20:10:14 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	move_ant(t_dlist *way, char *room, int end[2])
{
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
			if (ft_strequ(way->data, room))
				return ;
		}
	}
}

int		check_if_free_room(t_dlist **ways, t_dlist *way, int pos, int end[2])
{
	int		i;
	t_dlist	*tmp;

	i = -1;
	while (ways[++i])
	{
		tmp = ways[i];
		if (i != pos)
			while (tmp)
			{
				if (ft_strequ(tmp->data, way->data) &&
				tmp->data_size && i < pos)
					return (0);
				if (ft_strequ(tmp->data, way->data) &&
				tmp->data_size)
				{
					move_ant(ways[i], way->data, end);
					break ;
				}
				tmp = tmp->next;
			}
	}
	return (1);
}

void	send_ants_help(int end[2], t_dlist **ways, int pos)
{
	t_dlist	*way;

	way = ways[pos];
	ft_dlst_toend(&way);
	while (way->prev)
	{
		way = way->prev;
		if (way->data_size && check_if_free_room(ways, way->next, pos, end))
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
	int	i;

	i = -1;
	end[1] = 0;
	
	while (ways[++i])
	{
		send_ants_help(end, ways, i);
		if (*cur <= a_num && !(ways[i])->data_size)
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
	int	cur;
	int	end[2];

	cur = 1;
	end[0] = 0;
	while (input)
	{
		ft_printf("%s\n", input->content);
		input = input->next;
	}
	ft_printf("\n");
	if (ft_dlstlen(ways[0]) == 1)
		while (end[0] < a_num)
		{
			ft_printf("L%d-%s\n", cur, (ways[0])->data);
			cur++;
			end[0] += 1;
		}
	while (end[0] < a_num)
	{
		// usleep(100000);
		send_ants(ways, a_num, &cur, end);
		ft_printf("\n");
	}
}
