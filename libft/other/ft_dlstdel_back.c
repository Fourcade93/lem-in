/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 20:39:10 by fmallaba          #+#    #+#             */
/*   Updated: 2017/12/30 20:39:14 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdel_back(t_dlist **alst, void (*del)(void *, size_t))
{
	t_dlist	*tmp;

	if (!alst)
		return ;
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	ft_dlstdelone(&tmp, del);
}
