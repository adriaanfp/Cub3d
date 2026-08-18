/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 21:22:52 by jugarcia          #+#    #+#             */
/*   Updated: 2026/08/04 21:22:52 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_data *data, char *file)
{
	if (parse_file(file, data))
		return (1);
	if (init_player(data))
		return (1);
	if (init_mlx(data))
		return (1);
	if (load_textures(data))
	{
		print_error("Error al cargar las texturas");
		return (1);
	}
	return (0);
}
