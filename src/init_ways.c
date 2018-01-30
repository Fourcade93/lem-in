/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:23:13 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/30 13:35:49 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int check_ways(t_main main, int i)
{
    int j;
    t_dlist *tmp;
    t_dlist *tmp2;

    tmp = main.ways[i];
    while (tmp->next)
    {
        j = -1;
        while (++j < i)
        {
            tmp2 = main.ways[j];
            while (tmp2->next)
            {
                if (ft_strequ(tmp->data, tmp2->data))
                {
                    ft_dlstdel(&(main.ways[i]), ft_del_content);
                    return (0);
                }
                tmp2 = tmp2->next;
            }
        }
        tmp = tmp->next;
    }
    return (1);
}

void fill_way(t_main main, t_list *min, int i)
{
    t_list *tmp;
    int weight;

    ft_dlstadd(&(main.ways[i]), ft_dlstnew(main.end->name,
                            ft_strlen(main.end->name) + 1));
    ft_dlstadd(&(main.ways[i]), ft_dlstnew(((t_room *)(min->content))->name,
                            ft_strlen(((t_room *)(min->content))->name) + 1));
    weight = min->content_size - 1;
    tmp = min;
    while (1)
    {
        tmp = ((t_room *)(tmp->content))->connect;
        while (tmp)
        {
            if (((t_room *)(tmp->content))->weight == weight - 1)
                break;
            tmp = tmp->next;
        }
        if (ft_strequ(((t_room *)(tmp->content))->name, main.start->name))
            break;
        ft_dlstadd(&(main.ways[i]), ft_dlstnew(((t_room *)(tmp->content))->name,
                                    ft_strlen(((t_room *)(tmp->content))->name) + 1));
        weight--;
    }
}

t_list  *get_min_way(t_list *tmp, t_list *min, int min_len)
{
    while (tmp)
    {
        if ((int)tmp->content_size > min_len &&
            tmp->content_size < min->content_size)
            min = tmp;
        tmp = tmp->next;
    }
    return (min);
}

void init_other_ways(t_main main, int num)
{
    int i;
    int min_len;
    t_list *max;
    t_list *min;
    t_list *tmp;

    i = 1;
    min_len = ft_dlstlen(main.ways[0]);
    tmp = main.end->connect;
    max = tmp;
    while ((tmp = tmp->next))
        if (max->content_size < tmp->content_size)
            max = tmp;
    while (i < num)
    {
        tmp = main.end->connect;
        min = max;
        min = get_min_way(tmp, min, min_len);
        (min->content_size == max->content_size) ? num = 0 : num;
        min_len = min->content_size;
        fill_way(main, min, i);
        if (check_ways(main, i))
            i++;
    }
}

void init_ways(t_main main, int num)
{
    t_list *tmp;
    t_list *min;

    tmp = main.end->connect;
    min = tmp;
    while ((tmp = tmp->next))
        if (min->content_size > tmp->content_size)
            min = tmp;
    fill_way(main, min, 0);
    init_other_ways(main, num);
}
