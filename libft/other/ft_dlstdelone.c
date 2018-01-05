/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 21:35:11 by fmallaba          #+#    #+#             */
/*   Updated: 2018/01/05 16:53:06 by fmallaba         ###   ########.fr       */
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
