/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:30:00 by lebroue           #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_point_wall(t_game *game, double x, double y)
{
	if (x < 0 || x >= game->data->map_width
		|| y < 0 || y >= game->data->map_height)
		return (1);
	return (game->data->map[(int)y][(int)x] == '1');
}

int	is_wall_collision(t_game *game, double new_x, double new_y)
{
	if (is_point_wall(game, new_x - PLAYER_RADIUS, new_y - PLAYER_RADIUS))
		return (1);
	if (is_point_wall(game, new_x + PLAYER_RADIUS, new_y - PLAYER_RADIUS))
		return (1);
	if (is_point_wall(game, new_x - PLAYER_RADIUS, new_y + PLAYER_RADIUS))
		return (1);
	return (is_point_wall(game, new_x + PLAYER_RADIUS, new_y + PLAYER_RADIUS));
}
