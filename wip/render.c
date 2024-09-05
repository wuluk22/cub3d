/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:34:31 by clegros           #+#    #+#             */
/*   Updated: 2024/09/05 12:34:33 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	draw_vertical_line(t_env *e, int x, int start, int end, int color)
{
	int	i;

	i = start;
	if (start < 0)
		start = 0;
	if (end >= SCREEN_HEIGHT)
		end = SCREEN_HEIGHT - 1;
	while (i <= end)
		e->data[i++ * SCREEN_WIDTH + x] = color;
}

int	get_wall_color(int map_x, int map_y, int side)
{
	int	color;
	int textures[] = {0xFC4AE0, 0xFFD5F8, 0xFFB7F4, 0xFD98ED, 0xFD75E8};
	int texture_id = worldMap[map_x][map_y];

	if (texture_id >= 1 && texture_id <= 4)
		color = textures[texture_id];
	else
		color = textures[0];
	if (side == 1)
		color /= 0.2;
	return (color);
}

int	render_scene(t_env *e)
{
	int	x;

	x = 0;
	move_player(e);
	while (x < SCREEN_WIDTH)
	{
		compute_ray_direction(e, x);
		initialize_map_coordinates(e);
		compute_delta_distances(e);
		calculate_step_and_side_dist(e);
		perform_dda(e);
		compute_perpendicular_wall_distance(e);
		calculate_line_positions(e);
		draw_ceiling_and_floor(e, x);
		draw_wall(e, x);
		x++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}
