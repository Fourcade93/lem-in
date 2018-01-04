/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 14:43:58 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/04 21:06:38 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
void	send_ants_help(int *end, int *check, t_dlist **ways, int pos);
int		check_if_free_room(t_dlist **ways, t_dlist *way, int pos, int *end, int *check)
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
				tmp->data_size)
					send_ants_help(&(*end), &(*check), ways, i);
				tmp = tmp->next;
			}
	}
	return (1);
}

void	send_ants_help(int *end, int *check, t_dlist **ways, int pos)
{
	t_dlist	*way;

	way = ways[pos];
	ft_dlst_toend(&way);
	while (way->prev)
	{
		way = way->prev;
		if (way->data_size && check_if_free_room(ways, way->next, pos, &(*end), &(*check)))
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
		send_ants_help(&(*end), &check, ways, i);
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

void	call_send_ants(t_dlist **ways, int a_num, t_list *input)
{
	int	cur;
	int	end;

	cur = 1;
	end = 0;
	while (input)
	{
		// ft_printf("%s\n", input->content);
		input = input->next;
	}
	ft_printf("\n");
	while (end < a_num)
	{
		usleep(100000);
		send_ants(ways, a_num, &cur, &end);
		ft_printf("\n");
	}
}
