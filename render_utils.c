/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_data + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_color(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_length + x
			* (tex->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

t_texture	*select_texture(t_data *data, int side, double ray_dir_x,
	double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (&data->tex_ea);
		else
			return (&data->tex_we);
	}
	else
	{
		if (ray_dir_y > 0)
			return (&data->tex_so);
		else
			return (&data->tex_no);
	}
}

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				my_mlx_pixel_put(data, x, y, data->map.ceiling_color);
			else
				my_mlx_pixel_put(data, x, y, data->map.floor_color);
			x++;
		}
		y++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** my_mlx_pixel_put - Pone un pixel en la imagen
** @data: Estructura principal del juego
** @x: Coordenada X
** @y: Coordenada Y
** @color: Color del pixel
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_data + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
** get_texture_color - Obtiene el color de un píxel de la textura
** @tex: Textura de la que extraer el color
** @x: Coordenada X en la textura
** @y: Coordenada Y en la textura
**
** Return: Color del píxel
*/
int	get_texture_color(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_length + x
			* (tex->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

/*
** select_texture - Selecciona la textura correcta según la orientación
** @data: Estructura principal del juego
** @side: Lado del muro (0 = vertical, 1 = horizontal)
** @ray_dir_x: Dirección X del rayo
** @ray_dir_y: Dirección Y del rayo
**
** Return: Puntero a la textura seleccionada
*/
t_texture	*select_texture(t_data *data, int side, double ray_dir_x,
	double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (&data->tex_ea);
		else
			return (&data->tex_we);
	}
	else
	{
		if (ray_dir_y > 0)
			return (&data->tex_so);
		else
			return (&data->tex_no);
	}
}

/*
** draw_background - Dibuja el fondo (techo y suelo)
** @data: Estructura principal del juego
*/
void	draw_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				my_mlx_pixel_put(data, x, y, data->map.ceiling_color);
			else
				my_mlx_pixel_put(data, x, y, data->map.floor_color);
			x++;
		}
		y++;
	}
}
