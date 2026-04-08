/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:30:00 by lebroue           #+#    #+#             */
/*   Updated: 2026/02/24 15:39:27 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <X11/keysym.h>

void	handle_movement_key(int keycode)
{
	if (keycode == XK_w)
		printf("W key pressed - Move forward\n");
	else if (keycode == XK_a)
		printf("A key pressed - Move left\n");
	else if (keycode == XK_s)
		printf("S key pressed - Move backward\n");
	else if (keycode == XK_d)
		printf("D key pressed - Move right\n");
}

void	handle_arrow_key(int keycode)
{
	if (keycode == XK_Left)
		printf("Left arrow pressed - Rotate left\n");
	else if (keycode == XK_Right)
		printf("Right arrow pressed - Rotate right\n");
	else if (keycode == XK_Up)
		printf("Up arrow pressed\n");
	else if (keycode == XK_Down)
		printf("Down arrow pressed\n");
}

void	handle_movement_release(int keycode)
{
	if (keycode == XK_w)
		printf("W key released\n");
	else if (keycode == XK_a)
		printf("A key released\n");
	else if (keycode == XK_s)
		printf("S key released\n");
	else if (keycode == XK_d)
		printf("D key released\n");
}

void	handle_arrow_release(int keycode)
{
	if (keycode == XK_Left)
		printf("Left arrow released\n");
	else if (keycode == XK_Right)
		printf("Right arrow released\n");
	else if (keycode == XK_Up)
		printf("Up arrow released\n");
	else if (keycode == XK_Down)
		printf("Down arrow released\n");
}
