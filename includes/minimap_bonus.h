/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 13:58:22 by lebroue           #+#    #+#             */
/*   Updated: 2026/02/26 21:16:00 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H

typedef struct s_game	t_game;

// Total pixel size of the minimap on screen
# define MINIMAP_SIZE		200
// Number of cells visible in each direction from the player
# define MINIMAP_RANGE		5
// Screen position of the minimap top-left corner
# define MINIMAP_OFFSET_X	10
# define MINIMAP_OFFSET_Y	10

// Minimap colors (ARGB)
# define MINIMAP_COLOR_WALL		0xFFFFFF
# define MINIMAP_COLOR_FLOOR	0x222222
# define MINIMAP_COLOR_VOID		0x444444
# define MINIMAP_COLOR_PLAYER	0xFF0000
# define MINIMAP_COLOR_BORDER	0x888888

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////MINIMAP RENDERING///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/*DRAW MINIMAP: RENDER A PLAYER-CENTERED MINIMAP OF FIXED SCREEN SIZE*/
void					draw_minimap(t_game *game);

#endif
