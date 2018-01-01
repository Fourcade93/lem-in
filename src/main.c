/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:23:40 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/01 15:45:34 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list	*read_input(int *ants_num)
{
	t_list	*list;
	char	*line;

	list = NULL;
	while (get_next_line(0, &line))
	{
		ft_list_pushback(&list, ft_lstnew(line, ft_strlen(line) + 1));
		ft_memdel((void**)(&line));
	}
	return (valid_input(list, &(*ants_num)));
}

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

int		main(void)
{
	t_list	*rooms;
	t_dlist	**ways;
	int		ways_num;
	int		i;
	int		ants_num;

	rooms = read_input(&ants_num);
	ways_num = check_ways_num(rooms);
	ways = (t_dlist**)malloc(sizeof(t_dlist*) * (ways_num + 1));
	i = ways_num;
	while (i >= 0)
		ways[i--] = NULL;
	call_find_way(rooms, ways, ways_num);
	call_send_ants(ways, ants_num);
	i = -1;
	while (ways[++i])
		ft_dlstdel(&(ways[i]), &ft_del_content);
	free(ways);
	ft_lstdel(&rooms, &delone_room);
	return (0);
}
