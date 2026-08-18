/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 00:00:00 by                   #+#    #+#             */
/*   Updated: 2026/08/04 23:11:52 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** parse_file - Parsea el archivo .cub y carga la configuración
** @filename: Nombre del archivo a parsear
** @data: Estructura principal del juego
**
** Return: 0 si es exitoso, 1 si hay error
*/
static int	open_map_file(char *filename)
{
	int	fd;

	if (!check_file_extension(filename))
	{
		print_error("El archivo debe tener extensión .cub");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("No se pudo abrir el archivo");
		return (-1);
	}
	return (fd);
}

static int	parse_file_content(int fd, t_map *map)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while (line)
	{
		result = parse_line(line, map);
		if (result == 1)
		{
			free(line);
			print_error("Error en el formato del archivo");
			return (1);
		}
		if (result == 2)
		{
			if (read_map_grid(fd, map, line))
				return (free(line), print_error("Error al leer el mapa"), 1);
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_file(char *filename, t_data *data)
{
	int	fd;
	int	error;

	fd = open_map_file(filename);
	if (fd == -1)
		return (1);
	init_map(&data->map);
	error = parse_file_content(fd, &data->map);
	close(fd);
	if (error)
		return (1);
	return (validate_config(&data->map));
}
