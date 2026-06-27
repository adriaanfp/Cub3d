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
** print_error - Imprime un mensaje de error en stderr
** @message: Mensaje de error a mostrar
*/
void	print_error(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, 0);
	while (*message)
	{
		message++;
		write(2, message - 1, 1);
	}
	write(2, "\n", 1);
}

/*
** free_map - Libera toda la memoria asociada al mapa
** @map: Puntero a la estructura del mapa
*/
void	free_map(t_map *map)
{
	int	i;

	if (map->no_texture)
		free(map->no_texture);
	if (map->so_texture)
		free(map->so_texture);
	if (map->we_texture)
		free(map->we_texture);
	if (map->ea_texture)
		free(map->ea_texture);
	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
}

/*
** check_file_extension - Verifica que el archivo tenga extensión .cub
** @filename: Nombre del archivo a verificar
**
** Return: 1 si es válido, 0 si no
*/
static int	check_file_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 5)
		return (0);
	if (filename[len - 4] != '.' || filename[len - 3] != 'c'
		|| filename[len - 2] != 'u' || filename[len - 1] != 'b')
		return (0);
	return (1);
}

/*
** init_map - Inicializa la estructura del mapa con valores por defecto
** @map: Puntero a la estructura del mapa
*/
static void	init_map(t_map *map)
{
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
}

/*
** parse_file - Parsea el archivo .cub y carga la configuración
** @filename: Nombre del archivo a parsear
** @data: Estructura principal del juego
**
** Return: 0 si es exitoso, 1 si hay error
*/
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
	close(fd);
	return (0);
}
