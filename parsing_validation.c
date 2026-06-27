/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

static int	check_wall_at_position(t_map *map, int y, int x)
{
	if (y == 0 || y == map->height - 1)
	{
		print_error("El mapa no está cerrado por muros");
		return (1);
	}
	if (x == 0 || !map->grid[y][x + 1])
	{
		print_error("El mapa no está cerrado por muros");
		return (1);
	}
	if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' '
		|| (x > 0 && map->grid[y][x - 1] == ' ')
		|| map->grid[y][x + 1] == ' ')
	{
		print_error("El mapa no está cerrado por muros");
		return (1);
	}
	return (0);
}

int	check_map_walls(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (!is_valid_map_char(map->grid[y][x]))
			{
				print_error("Carácter inválido en el mapa");
				return (1);
			}
			if (map->grid[y][x] == '0' || map->grid[y][x] == 'N'
				|| map->grid[y][x] == 'S' || map->grid[y][x] == 'E'
				|| map->grid[y][x] == 'W')
			{
				if (check_wall_at_position(map, y, x))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_config(t_map *map)
{
	if (!map->no_texture || !map->so_texture
		|| !map->we_texture || !map->ea_texture)
	{
		print_error("Faltan texturas en el archivo");
		return (1);
	}
	if (map->floor_color == -1 || map->ceiling_color == -1)
	{
		print_error("Faltan colores en el archivo");
		return (1);
	}
	if (!map->grid || map->height == 0)
	{
		print_error("Falta el mapa en el archivo");
		return (1);
	}
	if (check_map_walls(map))
		return (1);
	return (0);
}
