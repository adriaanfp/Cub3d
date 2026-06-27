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

/*
** parse_file - Parsea el archivo .cub y carga la configuración
** @filename: Nombre del archivo a parsear
** @data: Estructura principal del juego
**
** Return: 0 si es exitoso, 1 si hay error
*/
int	parse_file(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		result;

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
	close(fd);
	return (validate_config(&data->map));
}
