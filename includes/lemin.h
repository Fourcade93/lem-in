/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 12:21:29 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/30 13:43:59 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define START "##start"
# define END "##end"
# define CHECK !ft_strchr(line, ' ') || !ft_strchr(ft_strchr(line, ' ') + 1, ' ') || ft_strchr(ft_strchr(ft_strchr(line, ' ') + 1, ' ') + 1, ' ')

typedef struct		s_room
{
	char			*name;
	char			*tag;
	int				x;
	int				y;
	// t_list			*ways;
	int				weight;
	t_list			*connect;
	struct s_room	*next;
}					t_room;

typedef struct		s_main
{
	int				ants;
	t_room			*start;
	t_room			*end;
	t_room			*rooms;
	t_dlist			**ways;
	t_list			*out;
}					t_main;

void 				read_input(t_main *main, t_room **rooms);
char				*get_rooms(t_main *main, t_room **rooms);
void				get_connects(t_main main, t_room *rooms, char *line);

int					only_digit(char *str);
int					arrlen(char **arr, int num);

t_dlist				**get_ways(t_main main, t_room *rooms);
void				start_search(t_list *arr);
void				init_ways(t_main main, int num);

void				call_send_ants(t_dlist **ways, int a_num, t_list *input);

void 				error_mngr(char *error, t_room *rooms);
void				dont_del(void *content, size_t size);

#endif
