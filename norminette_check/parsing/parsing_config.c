/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 00:00:00 by                   #+#    #+#             */
/*   Updated: 2026/08/04 23:03:40 by jugarcia         ###   ########.fr       */
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

static int	parse_rgb_component(char *str, int *i)
{
	int	value;

	value = 0;
	if (str[*i] < '0' || str[*i] > '9')
		return (-1);
	while (str[*i] >= '0' && str[*i] <= '9')
		value = value * 10 + (str[(*i)++] - '0');
	if (value > 255)
		return (-1);
	return (value);
}

static int	parse_color_value(char *str)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	r = parse_rgb_component(str, &i);
	if (r == -1 || str[i++] != ',')
		return (-1);
	g = parse_rgb_component(str, &i);
	if (g == -1 || str[i++] != ',')
		return (-1);
	b = parse_rgb_component(str, &i);
	if (b == -1 || str[i] != '\0')
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
