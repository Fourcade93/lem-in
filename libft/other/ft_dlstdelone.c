/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 21:35:11 by fmallaba          #+#    #+#             */
/*   Updated: 2017/11/17 18:49:13 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdelone(t_dlist **alst, void (*del)(void *, size_t))
{
	if (alst != NULL && del != NULL)
		if (*alst)
		{
			del((*alst)->data, (*alst)->data_size);
			free(*alst);
			(*alst) = NULL;
		}
}
