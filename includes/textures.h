/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:02:51 by lebroue           #+#    #+#             */
/*   Updated: 2026/04/06 19:50:16 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H

# define TEXTURES_H
# include "../libft/includes/libft.h"
# include "parsing.h"

typedef struct s_file_data	t_file_data;
typedef struct s_game		t_game;

typedef struct s_texture_load_buffers
{
	void					**image_ptr;
	char					**buffer_ptr;
	int						*width_ptr;
	int						*height_ptr;
	int						*line_len_ptr;
	int						*bpp_ptr;
	int						*endian_ptr;
}							t_texture_load_buffers;

typedef struct s_wall_texture
{
	// MLX image pointer for the texture
	void					*image_ptr;
	// Pixel buffer containing texture data (ARGB format)
	char					*pixel_buffer;
	// Texture width in pixels
	int						width;
	// Texture height in pixels
	int						height;
	// Bits per pixel (typically 32)
	int						bits_per_pixel;
	// Bytes per scanline (pitch for memory layout)
	int						bytes_per_scanline;
	// Byte order (0=little endian, 1=big endian)
	int						byte_order;
}							t_wall_texture;

typedef struct s_textures
{
	// Global texture dimensions
	int						global_width;
	int						global_height;

	// Individual wall textures
	t_wall_texture			north;
	t_wall_texture			south;
	t_wall_texture			east;
	t_wall_texture			west;
}							t_textures;

///////////////////////////////////////////////////////////////////////////////
///////////////////////TEXTURE LOADING & MANAGEMEN/////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/*LOAD TEXTURE:
Load all textures from file_data*/
int							load_textures(t_game *game, t_file_data *data);

/*LOAD TEXTURE BY FACE:
LOAD A SINGLE TEXTURE FILE (.xpm) FOR A SPECIFIC WALL FACE (N/S/E/W)*/
int							load_texture_by_face(t_game *game, char *path,
								char face);

///////////////////////////////////////////////////////////////////////////////
///////////////////////TEXTURE POINTER ACCESSORS///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/*GET NORTH PTRS: GET AND INITIALIZE TEXTURE DATA POINTERS FOR THE NORTH WALL*/
void						get_south_face_ptrs(t_game *game,
								t_texture_load_buffers *tex);

/*GET SOUTH PTRS: GET AND INITIALIZE TEXTURE DATA POINTERS FOR THE SOUTH WALL*/
void						get_north_face_ptrs(t_game *game,
								t_texture_load_buffers *tex);

/*GET EAST PTRS: GET AND INITIALIZE TEXTURE DATA POINTERS FOR THE EAST WALL*/
void						get_west_face_ptrs(t_game *game,
								t_texture_load_buffers *tex);

/*GET WEST PTRS: GET AND INITIALIZE TEXTURE DATA POINTERS FOR THE WEST WALL*/
void						get_east_face_ptrs(t_game *game,
								t_texture_load_buffers *tex);

/*GET TEXTURE PTRS: DISPATCHER FUNCTION
	- ROUTE TO CORRECT WALL-SPECIFIC POINTER GETTER (N/S/E/W)*/
void						get_texture_ptrs(t_game *game, char face,
								t_texture_load_buffers *tex);

///////////////////////////////////////////////////////////////////////////////
//////////////////////////CLEANUP & DEALLOCATION/////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/*FREE TEXTURES: FREE ALL LOADED TEXTURES AND DESTROY MLX IMAGE POINTERS*/
void						free_textures(t_game *game);

#endif 
