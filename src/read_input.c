/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 12:51:16 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/28 18:09:33 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		only_digit(char *str)
{
	int	i;
	if (!*str)
		return (0);
	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	if (ft_strlen(str) > 10 ||
		(ft_strlen(str) == 10 && ft_atoi(str) < 0))
		return (0);
	return (1);
}

int		arrlen(char **arr, int num)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	if (i != num)
	{
		i = -1;
		while (arr[++i])
			ft_strdel(&(arr[i]));
		free(arr);
		return (0);
	}
	return (1);
}

void	read_input(t_main *main, t_room **rooms)
{
	char	*line;

	(void)rooms;
	while (get_next_line(0, &line))
	{
		if (only_digit(line))
		{
			if (ft_atoi(line) == 0)
				error_mngr("ERROR of ants num!\n", NULL);
			(*main).ants = ft_atoi(line);
			break ;
		}
		else if (*line != '#' || (ft_strequ(START, line) || ft_strequ(END, line)))
			error_mngr("ERROR of ants num!\n", NULL);
		ft_list_pushback(&((*main).out), ft_lstnew(line, ft_strlen(line) + 1));
		ft_strdel(&line);
	}
	ft_strdel(&line);
	line = get_rooms(&(*main), &(*rooms));
	if (!(*main).start || !(*main).end)
		error_mngr("ERROR! Start or end missing!\n", *rooms);
	get_connects(*main, *rooms, line);
}
