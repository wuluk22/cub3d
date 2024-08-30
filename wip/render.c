#include "includes/cub3D.h"

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