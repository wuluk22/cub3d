#include "includes/cub3D.h"

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