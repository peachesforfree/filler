/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 22:00:54 by sbalcort          #+#    #+#             */
/*   Updated: 2017/11/03 21:07:33 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list		*get_fd(t_list **channel, int fd)
{
	t_list *tmp;

	tmp = *channel;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", 1);
	tmp->content_size = fd;
	ft_lstadd(channel, tmp);
	tmp = *channel;
	return (tmp);
}

static int			parse_string(t_list *current, char **line)
{
	char	*temp;
	char	*nl;

	nl = ft_strchr((char*)current->content, '\n');
	nl[0] = '\0';
	temp = current->content;
	if (!(*line = ft_strdup(current->content)))
		return (-1);
	if (nl)
		if (!(current->content = ft_strdup(nl + 1)))
			return (-1);
	if (*temp)
		ft_strdel(&temp);
	return (1);
}

static int			excess_lines(t_list *current, char **line)
{
	*line = ft_strdup(current->content);
	if (*(char*)current->content)
		ft_bzero((void*)current->content, sizeof(current->content));
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*channel;
	t_list			*current;
	char			buffer[BUFF_SIZE + 1];
	size_t			buff_count;

	if (fd < 0 || !line || (read(fd, buffer, 0) < 0) || (BUFF_SIZE < 1))
		return (-1);
	current = get_fd(&channel, fd);
	buff_count = 1;
	while (!ft_strchr((char*)current->content, '\n') && buff_count)
	{
		buff_count = read(fd, buffer, BUFF_SIZE);
		buffer[buff_count] = '\0';
		if (!(current->content = ft_strnjoin(current->content, buffer, 1)))
			return (-1);
	}
	if (ft_strchr((char*)current->content, '\n'))
		return (parse_string(current, line));
	if (*(char*)current->content)
		return (excess_lines(current, line));
	*line = NULL;
	return (0);
}
