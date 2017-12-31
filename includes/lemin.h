/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:32:22 by fmallaba          #+#    #+#             */
/*   Updated: 2017/12/31 18:58:13 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define START "##start"
# define END "##end"
# define MARK "mark"
# define ER_NUM_ANTS "Error! Ants num misssing!"
# define ER_START_END "Error start or end!"
# define ER_ROOM "Error! Not a valid rooms!"
# define ER_ROOM_CONNECTS "Error! Not valid room connects!"

typedef struct		s_room
{
	char			*name;
	char			*tag;
	int				x;
	int				y;
	t_list			*connect;
}					t_room;

void				delone_room(void *content, size_t size);
t_room	*check_room(char *str, char *tag);
t_list	*check_all_rooms(t_list **list, t_list *rooms);
int		check_connections(t_list *rooms, t_list *list);
void	error_mngr(int error, t_list *list, t_list *rooms);
t_list	*valid_input(t_list *list, int *ants_num);
int		find_way(t_list *connect, t_list **ways, int num[2], int count);
void	call_find_way(t_list *rooms, t_list **ways, int	ways_num);
int		check_ways_num(t_list *rooms);

#endif