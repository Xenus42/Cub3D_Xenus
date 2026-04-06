/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:07:27 by hadia             #+#    #+#             */
/*   Updated: 2026/04/03 16:51:47 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H
# include "../libft/includes/libft.h"

typedef struct s_list	t_list;
typedef struct s_game	t_game;

typedef struct s_file_data
{
	// Path to north wall texture
	char				*north_texture;
	// Path to south wall texture
	char				*south_texture;
	// Path to west wall texture
	char				*west_texture;
	// Path to east wall texture
	char				*east_texture;
	// Floor color RGB components [R, G, B]
	int					floor_color[3];
	// Ceiling color RGB components [R, G, B]
	int					ceiling_color[3];
	// Flag: floor color parsed
	int					floor_set;
	// Flag: ceiling color parsed
	int					ceiling_set;
	// Player starting X position on map (in cells)
	int					player_pos_x;
	// Player starting Y position on map (in cells)
	int					player_pos_y;
	// Player starting direction (N/S/E/W)
	char				player_dir;
	// 2D array of map (rows of cells)
	char				**map;
	// Map width in cells
	int					map_width;
	// Map height in cells
	int					map_height;
	// Flag: map parsing has started
	int					has_map_started;
	// Linked list of map lines (for parsing phase)
	t_list				*map_lines;
}						t_file_data;

/* PARSE_FILE: READ THE FILE LINE BY LINE AND SEND THE LINE TO PARSE_LINE */
int						parse_file(t_file_data *data, const char *file);
/* PARSE_LINE: PARSE A LINE OF THE MAP FILE DEPENDING ON WHAT THE FILE IS */
int						parse_line(t_file_data *data, char *line);
/* PARSE_MAP_LINE: PARSE A LINE THAT REPRESENT A PART OF THE MAP */
int						parse_map_line(t_file_data *data, char *line);
/* PARSE_COLOR_LINE: PARSE A LINE THAT REPRESENT A COLOR (FLOOR, OR CEILING) */
int						parse_color_line(t_file_data *data, char *line);

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////MEMORY CLEANUP///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/*FREE FILE DATA: DEALLOCATE ALL DYNAMICALLY ALLOCATED FILE DATA MEMORY*/
void					free_file_data(t_file_data *data);

/*FREE GAME: DEALLOCATE ALL GAME RESOURCES AND CLEANUP BEFORE EXIT*/
void					free_game(t_game *game);

#endif
