/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char *line, t_map *map)
{
	char	*path;
	int		i;

	i = 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	path = ft_strtrim(&line[i]);
	if (!path)
		return (1);
	if (ft_strncmp(line, "NO", 2) == 0 && !map->no_texture)
		map->no_texture = path;
	else if (ft_strncmp(line, "SO", 2) == 0 && !map->so_texture)
		map->so_texture = path;
	else if (ft_strncmp(line, "WE", 2) == 0 && !map->we_texture)
		map->we_texture = path;
	else if (ft_strncmp(line, "EA", 2) == 0 && !map->ea_texture)
		map->ea_texture = path;
	else
	{
		free(path);
		return (1);
	}
	return (0);
}

static int	parse_color_value(char *str)
{
	int	r;
	int	g;
	int	b;
	int	i;

	r = 0;
	i = 0;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		r = r * 10 + (str[i++] - '0');
	if (str[i++] != ',' || r > 255 || r < 0)
		return (-1);
	g = 0;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		g = g * 10 + (str[i++] - '0');
	if (str[i++] != ',' || g > 255 || g < 0)
		return (-1);
	b = 0;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		b = b * 10 + (str[i++] - '0');
	if (b > 255 || b < 0 || str[i] != '\0')
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int	parse_color(char *line, t_map *map)
{
	char	*color_str;
	int		color;
	int		i;

	i = 1;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	color_str = ft_strtrim(&line[i]);
	if (!color_str)
		return (1);
	color = parse_color_value(color_str);
	free(color_str);
	if (color == -1)
		return (1);
	if (line[0] == 'F' && map->floor_color == -1)
		map->floor_color = color;
	else if (line[0] == 'C' && map->ceiling_color == -1)
		map->ceiling_color = color;
	else
		return (1);
	return (0);
}

int	parse_line(char *line, t_map *map)
{
	char	*trimmed;
	int		result;

	trimmed = ft_strtrim(line);
	if (!trimmed || ft_strlen(trimmed) == 0)
	{
		if (trimmed)
			free(trimmed);
		return (0);
	}
	if (ft_strncmp(trimmed, "NO", 2) == 0 || ft_strncmp(trimmed, "SO", 2) == 0
		|| ft_strncmp(trimmed, "WE", 2) == 0
		|| ft_strncmp(trimmed, "EA", 2) == 0)
		result = parse_texture(trimmed, map);
	else if (trimmed[0] == 'F' || trimmed[0] == 'C')
		result = parse_color(trimmed, map);
	else if (is_map_line(trimmed))
		result = 2;
	else
		result = 1;
	free(trimmed);
	return (result);
}
