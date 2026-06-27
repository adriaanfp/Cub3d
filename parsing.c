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
** parse_texture - Parsea una línea de textura (NO, SO, WE, EA)
** @line: Línea a parsear
** @map: Estructura del mapa
**
** Return: 0 si es exitoso, 1 si hay error
*/
static int	parse_texture(char *line, t_map *map)
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

/*
** parse_color_value - Convierte una cadena RGB a un entero de color
** @str: Cadena con formato "R,G,B"
**
** Return: Color en formato int o -1 si hay error
*/
static int	parse_color_value(char *str)
{
	int	r;
	int	g;
	int	b;
	int	i;

	r = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		r = r * 10 + (str[i++] - '0');
	if (str[i++] != ',' || r > 255)
		return (-1);
	g = 0;
	while (str[i] >= '0' && str[i] <= '9')
		g = g * 10 + (str[i++] - '0');
	if (str[i++] != ',' || g > 255)
		return (-1);
	b = 0;
	while (str[i] >= '0' && str[i] <= '9')
		b = b * 10 + (str[i++] - '0');
	if (b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

/*
** parse_color - Parsea una línea de color (F o C)
** @line: Línea a parsear
** @map: Estructura del mapa
**
** Return: 0 si es exitoso, 1 si hay error
*/
static int	parse_color(char *line, t_map *map)
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

/*
** is_map_line - Verifica si una línea es parte del mapa
** @line: Línea a verificar
**
** Return: 1 si es línea de mapa, 0 si no
*/
static int	is_map_line(char *line)
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


/*
** read_map_grid - Lee el grid del mapa desde la línea actual
** @fd: File descriptor del archivo
** @map: Estructura del mapa
** @first_line: Primera línea del mapa ya leída
**
** Return: 0 si es exitoso, 1 si hay error
*/
static int	read_map_grid(int fd, t_map *map, char *first_line)
{
	char	*line;
	char	**temp_grid;
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
		{
			capacity *= 2;
			temp_grid = malloc(sizeof(char *) * capacity);
			if (!temp_grid)
				return (1);
			int j = 0;
			while (j < i)
			{
				temp_grid[j] = map->grid[j];
				j++;
			}
			free(map->grid);
			map->grid = temp_grid;
		}
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

/*
** parse_line - Parsea una línea del archivo
** @line: Línea a parsear
** @map: Estructura del mapa
**
** Return: 0 si es exitoso, 1 si hay error, 2 si es línea de mapa
*/
static int	parse_line(char *line, t_map *map)
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

/*
** init_player - Inicializa la posición y dirección del jugador
** @data: Estructura principal del juego
**
** Return: 0 si es exitoso, 1 si no se encuentra jugador
*/
int	init_player(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'N' || data->map.grid[y][x] == 'S'
				|| data->map.grid[y][x] == 'E' || data->map.grid[y][x] == 'W')
			{
				data->pos_x = x + 0.5;
				data->pos_y = y + 0.5;
				if (data->map.grid[y][x] == 'N')
				{
					data->dir_x = 0;
					data->dir_y = -1;
					data->plane_x = 0.66;
					data->plane_y = 0;
				}
				else if (data->map.grid[y][x] == 'S')
				{
					data->dir_x = 0;
					data->dir_y = 1;
					data->plane_x = -0.66;
					data->plane_y = 0;
				}
				else if (data->map.grid[y][x] == 'E')
				{
					data->dir_x = 1;
					data->dir_y = 0;
					data->plane_x = 0;
					data->plane_y = 0.66;
				}
				else if (data->map.grid[y][x] == 'W')
				{
					data->dir_x = -1;
					data->dir_y = 0;
					data->plane_x = 0;
					data->plane_y = -0.66;
				}
				return (0);
			}
			x++;
		}
		y++;
	}
	print_error("No se encontró jugador en el mapa");
	return (1);
}

/*
** validate_config - Valida que todos los elementos estén presentes
** @map: Estructura del mapa
**
** Return: 0 si es válido, 1 si falta algo
*/
static int	validate_config(t_map *map)
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
	return (0);
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
