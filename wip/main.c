/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:03:44 by clegros           #+#    #+#             */
/*   Updated: 2024/08/27 10:04:27 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int worldMap[MAP_WIDTH][MAP_HEIGHT] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int key_press(int keycode, t_env *e)
{
    if (keycode == KEY_ESC)
        exit(0);
    e->keys[keycode] = 1; // Marque la touche comme enfoncée
    return (0);
}

int key_release(int keycode, t_env *e)
{
    e->keys[keycode] = 0; // Marque la touche comme relâchée
    return (0);
}


void move_player(t_env *e)
{
    double moveSpeed = 0.05;  // Vitesse de déplacement
    double rotSpeed = 0.03;   // Vitesse de rotation

    // Mouvement avant/arrière
    if (e->keys[KEY_W])
    {
        if (worldMap[(int)(e->posX + e->dirX * moveSpeed)][(int)(e->posY)] == 0)
            e->posX += e->dirX * moveSpeed;
        if (worldMap[(int)(e->posX)][(int)(e->posY + e->dirY * moveSpeed)] == 0)
            e->posY += e->dirY * moveSpeed;
    }
    if (e->keys[KEY_S])
    {
        if (worldMap[(int)(e->posX - e->dirX * moveSpeed)][(int)(e->posY)] == 0)
            e->posX -= e->dirX * moveSpeed;
        if (worldMap[(int)(e->posX)][(int)(e->posY - e->dirY * moveSpeed)] == 0)
            e->posY -= e->dirY * moveSpeed;
    }

    // Mouvement gauche/droite
    if (e->keys[KEY_A])
    {
        if (worldMap[(int)(e->posX - e->planeX * moveSpeed)][(int)(e->posY)] == 0)
            e->posX -= e->planeX * moveSpeed;
        if (worldMap[(int)(e->posX)][(int)(e->posY - e->planeY * moveSpeed)] == 0)
            e->posY -= e->planeY * moveSpeed;
    }
    if (e->keys[KEY_D])
    {
        if (worldMap[(int)(e->posX + e->planeX * moveSpeed)][(int)(e->posY)] == 0)
            e->posX += e->planeX * moveSpeed;
        if (worldMap[(int)(e->posX)][(int)(e->posY + e->planeY * moveSpeed)] == 0)
            e->posY += e->planeY * moveSpeed;
    }
	if (e->keys[KEY_LEFT])
    {
        // Rotation à gauche
        double oldDirX = e->dirX;
        e->dirX = e->dirX * cos(-rotSpeed) - e->dirY * sin(-rotSpeed);
        e->dirY = oldDirX * sin(-rotSpeed) + e->dirY * cos(-rotSpeed);

        double oldPlaneX = e->planeX;
        e->planeX = e->planeX * cos(-rotSpeed) - e->planeY * sin(-rotSpeed);
        e->planeY = oldPlaneX * sin(-rotSpeed) + e->planeY * cos(-rotSpeed);
    }
    if (e->keys[KEY_RIGHT])
    {
        // Rotation à droite
        double oldDirX = e->dirX;
        e->dirX = e->dirX * cos(rotSpeed) - e->dirY * sin(rotSpeed);
        e->dirY = oldDirX * sin(rotSpeed) + e->dirY * cos(rotSpeed);

        double oldPlaneX = e->planeX;
        e->planeX = e->planeX * cos(rotSpeed) - e->planeY * sin(rotSpeed);
        e->planeY = oldPlaneX * sin(rotSpeed) + e->planeY * cos(rotSpeed);
    }
}

void draw_vertical_line(t_env *e, int x, int start, int end, int color)
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

void draw_minimap(t_env *e)
{
	int	mapScale;
	int	miniMapSize;
	int	mapStartX;
	int	mapStartY;
	int	x;
	int	y;
	int	i;
	int	j;
	int	drawX;
	int	drawY;
	int	color;

	mapScale = 4;
	miniMapSize = 100;
	mapStartX = SCREEN_WIDTH - miniMapSize - 20;
	mapStartY = 20;
	y = 0;
	while (y < e->mapHeight)
	{
		x = 0;
		while (x < e->mapWidth)
		{
			if (worldMap[y][x] > 0)
				color = 0xFFFFFF; // Couleur pour les murs
			else
				color = 0x000000; // Couleur pour les espaces vides
			i = 0;
			while (i < mapScale)
			{
				j = 0;
				while (j < mapScale)
				{
					drawX = mapStartX + x * mapScale + i;
					drawY = mapStartY + y * mapScale + j;
					if (drawX >= 0 && drawX < SCREEN_WIDTH && drawY >= 0 && drawY < SCREEN_HEIGHT)
						e->data[drawY * SCREEN_WIDTH + drawX] = color;
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
}


// Calcule la distance jusqu'à la prochaine intersection avec une ligne de la grille
void calculate_step_and_side_dist(t_env *e, double rayDirX, double rayDirY, int *stepX, int *stepY, double *sideDistX, double *sideDistY, int mapX, int mapY)
{
	if (rayDirX < 0)
	{
		*stepX = -1;
		*sideDistX = (e->posX - mapX) * fabs(1 / rayDirX);
	}
	else
	{
		*stepX = 1;
		*sideDistX = (mapX + 1.0 - e->posX) * fabs(1 / rayDirX);
	}
	if (rayDirY < 0)
	{
		*stepY = -1;
		*sideDistY = (e->posY - mapY) * fabs(1 / rayDirY);
	}
	else
	{
		*stepY = 1;
		*sideDistY = (mapY + 1.0 - e->posY) * fabs(1 / rayDirY);
	}
}

// Effectue le tracé de la ligne et détermine si elle a touché un mur
void perform_dda(t_env *e, int *mapX, int *mapY, double *sideDistX, double *sideDistY, double deltaDistX, double deltaDistY, int stepX, int stepY, int *side)
{
    int hit;

    hit = 0;
    (void)e;
    while (hit == 0)
    {
        if (*sideDistX < *sideDistY)
        {
            *sideDistX += deltaDistX;
            *mapX += stepX;
            *side = 0;
        }
        else
        {
            *sideDistY += deltaDistY;
            *mapY += stepY;
            *side = 1;
        }
        if (worldMap[*mapX][*mapY] > 0)
            hit = 1;
    }
}

// Calcule les positions pour dessiner les lignes
void calculate_line_positions(t_env *e, int *drawStart, int *drawEnd, double perpWallDist, int *lineHeight)
{
    (void)e;
    *lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
    *drawStart = -(*lineHeight) / 2 + SCREEN_HEIGHT / 2;
    if (*drawStart < 0)
        *drawStart = 0;
    *drawEnd = *lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (*drawEnd >= SCREEN_HEIGHT)
        *drawEnd = SCREEN_HEIGHT - 1;
}

// Remplit les parties de l'écran correspondant au plafond et au sol
void draw_ceiling_and_floor(t_env *e, int x, int drawStart, int drawEnd)
{
    int y;

    y = 0;
    while (y < drawStart)
    {
        if (y >= 0 && y < SCREEN_HEIGHT)
            e->data[y * SCREEN_WIDTH + x] = CEILING_COLOR;
        y++;
    }
    y = drawEnd + 1;
    while (y < SCREEN_HEIGHT)
    {
        if (y >= 0 && y < SCREEN_HEIGHT)
            e->data[y * SCREEN_WIDTH + x] = FLOOR_COLOR;
        y++;
    }
}

// Détermine la couleur du mur en fonction du numéro de texture
int get_wall_color(int mapX, int mapY, int side)
{
    int color;
    int textures[] = {0xFC4AE0, 0xFFD5F8, 0xFFB7F4, 0xFD98ED, 0xFD75E8};
    int textureID = worldMap[mapX][mapY];
    
    if (textureID >= 1 && textureID <= 4)
        color = textures[textureID];
    else
        color = textures[0]; // Default color (Yellow)
    // Ajuster la couleur si le mur est sur le côté
    if (side == 1)
        color /= 0.2;
    return (color);
}

// Fonction principale de rendu
int render_scene(t_env *e)
{
	int x;
	double cameraX, rayDirX, rayDirY;
	int mapX, mapY;
	double sideDistX, sideDistY;
	double deltaDistX, deltaDistY;
	int stepX, stepY, side;
	double perpWallDist;
	int lineHeight, drawStart, drawEnd;
	int color;

	x = 0;
	move_player(e);
	while (x < SCREEN_WIDTH)
	{
        // Calcul des coordonnées de la caméra et des directions du rayon
		cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		rayDirX = e->dirX + e->planeX * cameraX;
		rayDirY = e->dirY + e->planeY * cameraX;
        // Initialisation des coordonnées de la carte
        	mapX = (int)e->posX;
        	mapY = (int)e->posY;
        // Calcul des distances delta
        	if (rayDirX == 0)
            		deltaDistX = 1e30;
        	else
            		deltaDistX = fabs(1 / rayDirX);
        	if (rayDirY == 0)
            		deltaDistY = 1e30;
        	else
            		deltaDistY = fabs(1 / rayDirY);
        // Calcul de l'étape et des distances de côté
        	calculate_step_and_side_dist(e, rayDirX, rayDirY, &stepX, &stepY, &sideDistX, &sideDistY, mapX, mapY);
        	perform_dda(e, &mapX, &mapY, &sideDistX, &sideDistY, deltaDistX, deltaDistY, stepX, stepY, &side);
        // Calcul de la distance perpendiculaire au mur
        	if (side == 0)
            		perpWallDist = (mapX - e->posX + (1 - stepX) / 2) / rayDirX;
        	else
            		perpWallDist = (mapY - e->posY + (1 - stepY) / 2) / rayDirY;
        	calculate_line_positions(e, &drawStart, &drawEnd, perpWallDist, &lineHeight);
        	draw_ceiling_and_floor(e, x, drawStart, drawEnd);
        	color = get_wall_color(mapX, mapY, side);
        	draw_vertical_line(e, x, drawStart, drawEnd, color);
		x++;
	}
    // Dessin de la minimap
	draw_minimap(e);
    // Affichage de l'image à la fenêtre
    mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int main(void)
{
    t_env e;

    e.mlx = mlx_init();
    e.win = mlx_new_window(e.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
    e.img = mlx_new_image(e.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    e.data = (int *)mlx_get_data_addr(e.img, &e.bpp, &e.sizeline, &e.endian);
    e.posX = 15;
    e.posY = 15;
    e.dirX = -1;
    e.dirY = 0;
    e.planeX = 0;
    e.planeY = 0.66;
    e.mapHeight = MAP_HEIGHT;
    e.mapWidth = MAP_WIDTH;
    mlx_hook(e.win, 2, 1L << 0, &key_press, &e);
    mlx_hook(e.win, 3, 1L << 1, &key_release, &e);
    mlx_loop_hook(e.mlx, &render_scene, &e);
    mlx_loop(e.mlx);
    return (0);
}