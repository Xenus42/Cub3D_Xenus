/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ /*   Created: 2026/02/17 15:48:42 by lebroue           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

static int	get_rotated_cell_color(t_game *game, int dx, int dy, int cell_size)
{
	double	u;
	double	v;
	int		map_x;
	int		map_y;

	u = (double)dx / cell_size;
	v = -(double)dy / cell_size;
	map_x = (int)floor(game->player_pos_x
			- u * game->player_vector_direction_y
			+ v * game->player_vector_direction_x);
	map_y = (int)floor(game->player_pos_y
			+ u * game->player_vector_direction_x
			+ v * game->player_vector_direction_y);
	if (map_x < 0 || map_y < 0 || map_x >= game->data->map_width
		|| map_y >= game->data->map_height)
		return (MINIMAP_COLOR_VOID);
	if (map_x >= (int)ft_strlen(game->data->map[map_y]))
		return (MINIMAP_COLOR_VOID);
	if (game->data->map[map_y][map_x] == '1')
		return (MINIMAP_COLOR_WALL);
	return (MINIMAP_COLOR_FLOOR);
}

static int	blend_fov(int color)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) + 60;
	g = ((color >> 8) & 0xFF) + 50;
	b = (color & 0xFF) + 15;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

static int	get_pixel_color(t_game *game, int dx, int dy, int cell_size)
{
	int		color;
	double	cam_sq;

	color = get_rotated_cell_color(game, dx, dy, cell_size);
	cam_sq = game->camera_plane_x * game->camera_plane_x
		+ game->camera_plane_y * game->camera_plane_y;
	if (dy < 0 && cam_sq * (double)(dy * dy) >= (double)(dx * dx))
		return (blend_fov(color));
	return (color);
}

static void	draw_minimap_circle(t_game *game, int cx, int cy, int radius)
{
	int		dx;
	int		dy;
	int		cell_size;
	int		dist_sq;

	cell_size = radius / MINIMAP_RANGE;
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			dist_sq = dx * dx + dy * dy;
			if (dist_sq <= radius * radius)
			{
				if (dist_sq >= (radius - 2) * (radius - 2))
					put_pixel(game, cx + dx, cy + dy, MINIMAP_COLOR_BORDER);
				else
					put_pixel(game, cx + dx, cy + dy,
						get_pixel_color(game, dx, dy, cell_size));
			}
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_game *game)
{
	int	radius;
	int	cx;
	int	cy;
	int	i;
	int	j;

	radius = MINIMAP_SIZE / 2;
	cx = MINIMAP_OFFSET_X + radius;
	cy = MINIMAP_OFFSET_Y + radius;
	draw_minimap_circle(game, cx, cy, radius);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			put_pixel(game, cx + i, cy + j, MINIMAP_COLOR_PLAYER);
			j++;
		}
		i++;
	}
}
