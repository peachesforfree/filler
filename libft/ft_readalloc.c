/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 15:28:48 by sbalcort          #+#    #+#             */
/*   Updated: 2017/07/17 16:27:46 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		bigger_buffer(char *chr_buffer, int buffer_cnt)
{
	buffer_cnt *= 2;
	free(chr_buffer);
}

char		*ft_read_alloc(int fd)
{
	char	*content;
	char	*chr_buffer;
	int		buffer_cnt;
	int		read_count;

	buffer_cnt = 64;
	chr_buffer = ft_strnew(buffer_cnt);
	if (fd < 0 || (read(fd, &chr_buffer, 0) < 0))
		return (NULL);
	content = ft_strnew(1);
	while ((read_count = read(fd, chr_buffer, buffer_cnt)))
	{
		if (!(content = ft_strnjoin(content, chr_buffer, 1)))
		{
			free(&content);
			return (NULL);
		}
		if (read_count == buffer_cnt)
		{
			bigger_buffer(chr_buffer, buffer_cnt);
			chr_buffer = ft_strnew(buffer_cnt);
		}
	}
	free(chr_buffer);
	return (content);
}
