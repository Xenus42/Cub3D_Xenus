/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:30:00 by lebroue           #+#    #+#             */
/*   Updated: 2026/04/02 12:05:25 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_textures(t_game *game)
{
	if (game->textures.north.image_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures.north.image_ptr);
	if (game->textures.south.image_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures.south.image_ptr);
	if (game->textures.east.image_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures.east.image_ptr);
	if (game->textures.west.image_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures.west.image_ptr);
}
