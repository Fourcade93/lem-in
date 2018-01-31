/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:16:18 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/31 16:17:36 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		fill_way(t_main main, t_list *min, int i, int weight)
{
	while (min)
	{
		if (ft_strequ(((t_room *)(min->content))->tag, START))
			return (1);
		if (((t_room *)(min->content))->weight == weight - 1 &&
			!((t_room *)(min->content))->tag)
			if (fill_way(main, ((t_room *)(min->content))->connect,
			i, weight - 1))
			{
				ft_dlst_pushback(&(main.ways[i]),
						ft_dlstnew(((t_room *)(min->content))->name,
							ft_strlen(((t_room *)(min->content))->name) + 1));
				((t_room *)(min->content))->tag = main.mark;
				return (1);
			}
		min = min->next;
	}
	return (0);
}
