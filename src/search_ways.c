/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_ways.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:22:10 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/30 13:43:44 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void put_weight_to_end(t_list *connect, t_list *tmp)
{
    while (connect)
    {
        if (ft_strequ(((t_room *)(connect->content))->name, ((t_room *)(tmp->content))->name))
        {
            connect->content_size = ((t_room *)(tmp->content))->weight + 1;
            break;
        }
        connect = connect->next;
    }
}

t_list    *search_ways(t_list *connect, t_list *tmp, t_list *buf)
{
    while (connect)
    {
        if (ft_strequ(((t_room *)(connect->content))->tag, END))
            put_weight_to_end(((t_room *)(connect->content))->connect, tmp);
        else if ((((t_room *)(connect->content))->weight > ((t_room *)(tmp->content))->weight + 1 ||
                  ((t_room *)(connect->content))->weight == 0) &&
                 !ft_strequ(((t_room *)(connect->content))->tag, START))
        {
            ((t_room *)(connect->content))->weight = ((t_room *)(tmp->content))->weight + 1;
            ft_lstadd(&buf, ft_lstnew(NULL, 0));
            buf->content = connect->content;
        }
        connect = connect->next;
    }
	return (buf);
}

void start_search(t_list *arr)
{
    t_list *buf;
    t_list *tmp;
    t_list *connect;

    buf = NULL;
    while (ft_lstlen(arr) > 0)
    {
        tmp = arr;
        while (tmp)
        {
            connect = ((t_room *)(tmp->content))->connect;
            buf = search_ways(connect, tmp, buf);
            tmp = tmp->next;
        }
        ft_lstdel(&arr, dont_del);
        arr = buf;
        buf = NULL;
    }
}
