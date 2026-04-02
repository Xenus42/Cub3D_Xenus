/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_draw_vertical_line_utils_w        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:07:00 by lebroue           #+#    #+#             */
/*   Updated: 2026/04/02 12:05:24 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	fill_n_texture(t_game *game, t_texture_data *info)
{
	info->texture_pixel_buffer = game->textures.north.pixel_buffer;
	info->texture_width = game->textures.north.width;
	info->texture_height = game->textures.north.height;
	info->texture_bytes_per_scanline = game->textures.north.bytes_per_scanline;
}

static void	fill_s_texture(t_game *game, t_texture_data *info)
{
	info->texture_pixel_buffer = game->textures.south.pixel_buffer;
	info->texture_width = game->textures.south.width;
	info->texture_height = game->textures.south.height;
	info->texture_bytes_per_scanline = game->textures.south.bytes_per_scanline;
}

static void	fill_e_texture(t_game *game, t_texture_data *info)
{
	info->texture_pixel_buffer = game->textures.east.pixel_buffer;
	info->texture_width = game->textures.east.width;
	info->texture_height = game->textures.east.height;
	info->texture_bytes_per_scanline = game->textures.east.bytes_per_scanline;
}

static void	fill_w_texture(t_game *game, t_texture_data *info)
{
	info->texture_pixel_buffer = game->textures.west.pixel_buffer;
	info->texture_width = game->textures.west.width;
	info->texture_height = game->textures.west.height;
	info->texture_bytes_per_scanline = game->textures.west.bytes_per_scanline;
}

void	get_texture_data(t_game *game, char face, t_texture_data *info)
{
	if (face == 'N')
		fill_n_texture(game, info);
	else if (face == 'S')
		fill_s_texture(game, info);
	else if (face == 'E')
		fill_e_texture(game, info);
	else if (face == 'W')
		fill_w_texture(game, info);
}
