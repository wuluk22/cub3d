#include "includes/cub3D.h"

void	compute_ray_direction(t_env *e, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	e->ray_dir_x = e->dir_x + e->plane_x * camera_x;
	e->ray_dir_y = e->dir_y + e->plane_y * camera_x;
}

void	initialize_map_coordinates(t_env *e)
{
	e->map_x = (int)e->pos_x;
	e->map_y = (int)e->pos_y;
}

void	compute_delta_distances(t_env *e)
{
	if (e->ray_dir_x == 0)
		e->delta_dist_x = 1e30;
	else
		e->delta_dist_x = fabs(1 / e->ray_dir_x);
	if (e->ray_dir_y == 0)
		e->delta_dist_y = 1e30;
	else
		e->delta_dist_y = fabs(1 / e->ray_dir_y);
}

void	compute_perpendicular_wall_distance(t_env *e)
{
	if (e->side == 0)
		e->perp_wall_dist = (e->map_x - e->pos_x + (1 - e->step_x) / 2) / e->ray_dir_x;
	else
		e->perp_wall_dist = (e->map_y - e->pos_y + (1 - e->step_y) / 2) / e->ray_dir_y;
}

void	draw_wall(t_env *e, int x)
{
	int	color;

	color = get_wall_color(e->map_x, e->map_y, e->side);
	draw_vertical_line(e, x, e->draw_start, e->draw_end, color);
}
