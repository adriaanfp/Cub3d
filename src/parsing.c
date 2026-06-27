/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_file_lines(int fd, t_data *data)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while (line)
	{
		result = parse_line(line, &data->map);
		if (result == 1)
		{
			free(line);
			print_error("Error en el formato del archivo");
			close(fd);
			return (1);
		}
		if (result == 2)
		{
			if (read_map_grid(fd, &data->map, line))
			{
				free(line);
				print_error("Error al leer el mapa");
				close(fd);
				return (1);
			}
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_file(char *filename, t_data *data)
{
	int	fd;

	if (!check_file_extension(filename))
	{
		print_error("El archivo debe tener extensión .cub");
		return (1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("No se pudo abrir el archivo");
		return (1);
	}
	init_map(&data->map);
	if (process_file_lines(fd, data))
		return (1);
	close(fd);
	return (validate_config(&data->map));
}
