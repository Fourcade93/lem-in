/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallaba <fmallaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:38:01 by fmallaba          #+#    #+#             */
/*   Updated: 2017/12/25 20:39:10 by fmallaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int		delete_elem(t_list **list, int fd)
{
	t_list	*tmp;
	t_list	*buf;
	size_t	nfd;

	tmp = *list;
	nfd = fd;
	if (tmp->content_size == nfd)
	{
		buf = tmp->next;
		free(tmp->content);
		free(tmp);
		*list = buf;
		return (0);
	}
	while (tmp->next && tmp->next->content_size != nfd)
		tmp = tmp->next;
	buf = tmp->next->next;
	free(tmp->next->content);
	free(tmp->next);
	tmp->next = buf;
	return (0);
}

static void		get_line(t_list *temp, char **line)
{
	char	*buf;
	int		i;
	int		len;

	buf = (char *)(temp->content);
	len = ft_strlen(buf);
	if (ft_strchr(temp->content, 10))
	{
		i = 0;
		while (buf[i] != '\n')
			i++;
		*line = ft_strsub(buf, 0, i);
		if (len - i == 1)
			ft_bzero(buf, len);
		else
		{
			ft_memmove(buf, &buf[i + 1], len - i);
			ft_bzero(&buf[len - i], i);
		}
	}
	else
	{
		*line = ft_strdup(buf);
		ft_bzero(buf, len);
	}
}

static t_list	*get_list(t_list **list, int fd)
{
	t_list	*new;
	t_list	*temp;
	size_t	nfd;

	if (!(*list))
	{
		new = ft_lstnew(NULL, 0);
		new->content_size = fd;
		ft_lstadd(&(*list), new);
		return (*list);
	}
	temp = *list;
	nfd = fd;
	while (temp && temp->content_size != nfd)
		temp = temp->next;
	if (!temp)
	{
		new = ft_lstnew(NULL, 0);
		new->content_size = fd;
		ft_lstadd(&(*list), new);
		return (*list);
	}
	return (temp);
}

static char		*gnl_help(char buf[BUFF_SIZE + 1], char **tmp, int ret)
{
	char	*temp;
	char	*temp2;

	temp = ft_strsub(buf, 0, ret);
	if (*tmp)
	{
		temp2 = ft_strjoin(*tmp, temp);
		ft_strdel(&(*tmp));
		ft_strdel(&temp);
		return (temp2);
	}
	else
		return (temp);
}

int				get_next_line(const int fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	t_list			*temp;
	static t_list	*list;

	if (fd < 0 || !line)
		return (-1);
	temp = get_list(&list, fd);
	tmp = temp->content;
	ret = 0;
	if (!temp->content || (temp->content && !ft_strchr(temp->content, 10)))
		while ((ret = read(fd, &buf, BUFF_SIZE)) > 0)
			if (ft_strchr((tmp = gnl_help(buf, &tmp, ret)), 10))
				break ;
	temp->content = tmp;
	if (ret < 0)
		return (-1);
	if (!temp || !temp->content)
		return (0);
	if (ret == 0 && !ft_strlen(temp->content))
		return (delete_elem(&list, fd));
	get_line(temp, &(*line));
	return (1);
}
