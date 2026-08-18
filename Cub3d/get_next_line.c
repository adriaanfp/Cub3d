/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 00:00:00 by                   #+#    #+#             */
/*   Updated: 2026/08/04 15:19:11 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	refill_buffer(int fd, char *buffer, int *buffer_pos,
		int *buffer_read)
{
	if (*buffer_pos >= *buffer_read)
	{
		*buffer_read = read(fd, buffer, 1024);
		*buffer_pos = 0;
		if (*buffer_read <= 0)
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024];
	static int	buffer_pos;
	static int	buffer_read;
	char		line[1024];
	int			i;

	i = 0;
	while (refill_buffer(fd, buffer, &buffer_pos, &buffer_read))
	{
		line[i] = buffer[buffer_pos++];
		if (line[i] == '\n')
		{
			line[++i] = '\0';
			return (ft_strdup(line));
		}
		i++;
	}
	if (i == 0)
		return (NULL);
	line[i] = '\0';
	return (ft_strdup(line));
}
