/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_data *data)
{
	if (data->mlx_ptr)
	{
		if (data->tex_no.img != NULL)
			mlx_destroy_image(data->mlx_ptr, data->tex_no.img);
		if (data->tex_so.img != NULL)
			mlx_destroy_image(data->mlx_ptr, data->tex_so.img);
		if (data->tex_we.img != NULL)
			mlx_destroy_image(data->mlx_ptr, data->tex_we.img);
		if (data->tex_ea.img != NULL)
			mlx_destroy_image(data->mlx_ptr, data->tex_ea.img);
	}
}

static int	load_texture(t_data *data, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->mlx_ptr, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	return (0);
}

int	load_textures(t_data *data)
{
	if (load_texture(data, &data->tex_no, data->map.no_texture))
		return (1);
	if (load_texture(data, &data->tex_so, data->map.so_texture))
		return (1);
	if (load_texture(data, &data->tex_we, data->map.we_texture))
		return (1);
	if (load_texture(data, &data->tex_ea, data->map.ea_texture))
		return (1);
	return (0);
}
