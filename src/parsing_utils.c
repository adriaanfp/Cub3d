/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	free_map(t_map *map)
{
	int	i;

	if (map->no_texture != NULL)
		free(map->no_texture);
	if (map->so_texture != NULL)
		free(map->so_texture);
	if (map->we_texture != NULL)
		free(map->we_texture);
	if (map->ea_texture != NULL)
		free(map->ea_texture);
	if (map->grid != NULL)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i] != NULL)
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
}

int	check_file_extension(char *filename)
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

void	init_map(t_map *map)
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

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
