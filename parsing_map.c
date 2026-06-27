/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	expand_grid_capacity(t_map *map, int *capacity, int i)
{
	char	**temp_grid;
	int		j;

	*capacity *= 2;
	temp_grid = malloc(sizeof(char *) * (*capacity));
	if (!temp_grid)
		return (1);
	j = 0;
	while (j < i)
	{
		temp_grid[j] = map->grid[j];
		j++;
	}
	free(map->grid);
	map->grid = temp_grid;
	return (0);
}

int	read_map_grid(int fd, t_map *map, char *first_line)
{
	char	*line;
	int		capacity;
	int		i;

	capacity = 10;
	map->grid = malloc(sizeof(char *) * capacity);
	if (!map->grid)
		return (1);
	i = 0;
	map->grid[i] = ft_strtrim(first_line);
	if (ft_strlen(map->grid[i]) > map->width)
		map->width = ft_strlen(map->grid[i]);
	i++;
	line = get_next_line(fd);
	while (line)
	{
		if (i >= capacity - 1)
			if (expand_grid_capacity(map, &capacity, i))
				return (1);
		if (is_map_line(line) && ft_strlen(line) > 1)
		{
			map->grid[i] = ft_strtrim(line);
			if (ft_strlen(map->grid[i]) > map->width)
				map->width = ft_strlen(map->grid[i]);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	map->height = i;
	return (0);
}
