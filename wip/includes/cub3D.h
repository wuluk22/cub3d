/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:03:26 by clegros           #+#    #+#             */
/*   Updated: 2024/08/27 10:03:28 by clegros          ###   ########.fr       */
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
# define KEY_LEFT 124
# define KEY_RIGHT 123

typedef struct s_env
{
	void	*mlx;
	void	*win;
	void	*img;
	int	*data;
	int	bpp;
	int	sizeline;
	int	endian;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	mapHeight;
	double	mapWidth;
	int		keys[256];
}	t_env;

int key_press(int keycode, t_env *e);
int key_release(int keycode, t_env *e);
void move_player(t_env *e);
void draw_vertical_line(t_env *e, int x, int start, int end, int color);
void draw_minimap(t_env *e);
void calculate_step_and_side_dist(t_env *e, double rayDirX, double rayDirY, int *stepX, int *stepY, double *sideDistX, double *sideDistY, int mapX, int mapY);
void perform_dda(t_env *e, int *mapX, int *mapY, double *sideDistX, double *sideDistY, double deltaDistX, double deltaDistY, int stepX, int stepY, int *side);
void calculate_line_positions(t_env *e, int *drawStart, int *drawEnd, double perpWallDist, int *lineHeight);
void draw_ceiling_and_floor(t_env *e, int x, int drawStart, int drawEnd);
int get_wall_color(int mapX, int mapY, int side);
int render_scene(t_env *e);

#endif
