/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:34:13 by clegros           #+#    #+#             */
/*   Updated: 2024/09/05 12:34:15 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	key_press(int keycode, t_env *e)
{
	if (keycode == KEY_ESC)
		exit(0);
	e->keys[keycode] = 1;
	printf("Key pressed: %d\n", keycode);
	return (0);
}

int	key_release(int keycode, t_env *e)
{
	e->keys[keycode] = 0;
	printf("Key released: %d\n", keycode);
	return (0);
}

void	move_player(t_env *e)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.03;
	move_forward_backward(e, move_speed);
	move_left_right(e, move_speed);
	if (e->keys[KEY_LEFT] && !e->keys[KEY_RIGHT])
		rotate_left(e, rot_speed);
	if (e->keys[KEY_RIGHT] && !e->keys[KEY_LEFT])
		rotate_right(e, rot_speed);
}
