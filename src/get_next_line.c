/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_next_line(int fd)
{
	static char	buffer[1024];
	static int	buffer_pos;
	static int	buffer_read;
	char		line[1024];
	int			i;

	i = 0;
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, 1024);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		line[i] = buffer[buffer_pos++];
		if (line[i] == '\n')
		{
			line[++i] = '\0';
			return (ft_strdup(line));
		}
		i++;
	}
	if (i > 0)
	{
		line[i] = '\0';
		return (ft_strdup(line));
	}
	return (NULL);
}
