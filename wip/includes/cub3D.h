/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:03:26 by clegros           #+#    #+#             */
/*   Updated: 2024/09/12 15:15:50 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../utils/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
#include <stdio.h> // a enlever quand on aura mis ft_printf aml

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define CEILING_COLOR 0x000000
# define FLOOR_COLOR   0x9000FF
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124

extern int	worldMap[MAP_WIDTH][MAP_HEIGHT];

typedef struct s_map // ajoute par aml
{
	char	**map; // = worldmap ? aml
	char	**map_copy;
	int		x;
	int		y;
	int		player;
	int		fc;
	int		cc;
	int		x_map_size;
	int		y_map_size;
//	mlx_image_t		no; // ajout par aml
//	mlx_image_t		so; // ajout par aml
//	mlx_image_t		we; // ajout par aml
//	mlx_image_t		ea; // ajout par aml
	u_int32_t	floor_color; // ajout par aml
	u_int32_t	ceiling_color; // ajout par aml
}	t_map;

typedef struct s_env
{
	t_map	*map; // ajout par aml
	void	*mlx;
	void	*win;
	void	*img;
	int		*data;
	int		bpp;
	int		sizeline;
	int		endian;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		side;
	int		draw_start;
	int		draw_end;
	int		line_height;
	double	perp_wall_dist;
	double	map_height;
	double	map_width;
	int		keys[256];
}	t_env;

//-----------keymap_utils.c
void	move_forward_backward(t_env *e, double moveSpeed);
void	move_left_right(t_env *e, double moveSpeed);
void	rotate_left(t_env *e, double rotSpeed);
void	rotate_right(t_env *e, double rotSpeed);
//-----------keymap.c
int	key_press(int keycode, t_env *e);
int	key_release(int keycode, t_env *e);
void	move_player(t_env *e);
//-----------parsing_help.c
void	ft_exit(t_env *e, char *str, int i);
void	free_map(char **map, int i);
//-----------parsing_map.c
int		get_map(char **argv, t_env *e, t_map *map);
//-----------parsing.c
int		parsing(int argc, char **argv, t_map *map, t_env *e);
//-----------raycasting.c
void	calculate_step_and_side_dist(t_env *e);
void	perform_dda(t_env *e);
void	calculate_line_positions(t_env *e);
void	draw_ceiling_and_floor(t_env *e, int x);
//-----------render_utils.c
void	compute_ray_direction(t_env *e, int x);
void	initialize_map_coordinates(t_env *e);
void	compute_delta_distances(t_env *e);
void	compute_perpendicular_wall_distance(t_env *e);
void	draw_wall(t_env *e, int x);
//-----------render.c
void	draw_vertical_line(t_env *e, int x, int start, int end, int color);
int	get_wall_color(int map_x, int map_y, int side);
int	render_scene(t_env *e);


#endif
