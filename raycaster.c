#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define CEILING_COLOR 0x000000  // Light Blue color for the ceiling
#define FLOOR_COLOR   0x9000FF  // Brown color for the floor


int worldMap[MAP_WIDTH][MAP_HEIGHT] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

typedef struct s_env
{
    void	*mlx;
    void	*win;
    void	*img;
    int		*data;
    int		bpp;
    int		sizeline;
    int		endian;
    double	posX;
    double	posY;
    double	dirX;
    double	dirY;
    double	planeX;
    double	planeY;
    double  mapHeight;
    double  mapWidth;
}	t_env;

int	key_press(int keycode, t_env *e)
{
    double	moveSpeed;
    double	rotSpeed;
    double	oldDirX;
    double	oldPlaneX;

    moveSpeed = 0.5;
    rotSpeed = 0.10;
    if (keycode == 126)
    {
        if (worldMap[(int)(e->posX + e->dirX * moveSpeed)][(int)(e->posY)] == 0)
            e->posX += e->dirX * moveSpeed;
        if (worldMap[(int)(e->posX)][(int)(e->posY + e->dirY * moveSpeed)] == 0)
            e->posY += e->dirY * moveSpeed;
    }
    if (keycode == 125)
    {
        if (worldMap[(int)(e->posX - e->dirX * moveSpeed)][(int)(e->posY)] == 0)
            e->posX -= e->dirX * moveSpeed;
        if (worldMap[(int)(e->posX)][(int)(e->posY - e->dirY * moveSpeed)] == 0)
            e->posY -= e->dirY * moveSpeed;
    }
    if (keycode == 124)
    {
        oldDirX = e->dirX;
        e->dirX = e->dirX * cos(-rotSpeed) - e->dirY * sin(-rotSpeed);
        e->dirY = oldDirX * sin(-rotSpeed) + e->dirY * cos(-rotSpeed);
        oldPlaneX = e->planeX;
        e->planeX = e->planeX * cos(-rotSpeed) - e->planeY * sin(-rotSpeed);
        e->planeY = oldPlaneX * sin(-rotSpeed) + e->planeY * cos(-rotSpeed);
    }
    if (keycode == 123)
    {
        oldDirX = e->dirX;
        e->dirX = e->dirX * cos(rotSpeed) - e->dirY * sin(rotSpeed);
        e->dirY = oldDirX * sin(rotSpeed) + e->dirY * cos(rotSpeed);
        oldPlaneX = e->planeX;
        e->planeX = e->planeX * cos(rotSpeed) - e->planeY * sin(rotSpeed);
        e->planeY = oldPlaneX * sin(rotSpeed) + e->planeY * cos(rotSpeed);
    }
    if (keycode == 53)
        exit(0);
    return (0);
}

void draw_vertical_line(t_env *e, int x, int start, int end, int color)
{
    int i;

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
    int mapScale = 4; // Échelle de la minimap (une case = 4x4 pixels)
    int miniMapSize = 100; // Taille de la minimap
    int mapStartX = SCREEN_WIDTH - miniMapSize - 20; // Position X de la minimap
    int mapStartY = 20; // Position Y de la minimap

    // Dessiner la minimap
    for (int y = 0; y < e->mapHeight; y++)
    {
        for (int x = 0; x < e->mapWidth; x++)
        {
            int color;
            if (worldMap[y][x] > 0)
                color = 0xFFFFFF; // Couleur pour les murs
            else
                color = 0x000000; // Couleur pour les espaces vides

            for (int i = 0; i < mapScale; i++)
            {
                for (int j = 0; j < mapScale; j++)
                {
                    int drawX = mapStartX + x * mapScale + i;
                    int drawY = mapStartY + y * mapScale + j;

                    if (drawX >= 0 && drawX < SCREEN_WIDTH && drawY >= 0 && drawY < SCREEN_HEIGHT)
                        e->data[drawY * SCREEN_WIDTH + drawX] = color;
                }
            }
        }
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
    int hit = 0;

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
    for (int y = 0; y < drawStart; y++) {
        if (y >= 0 && y < SCREEN_HEIGHT)
            e->data[y * SCREEN_WIDTH + x] = CEILING_COLOR;
    }
    for (int y = drawEnd + 1; y < SCREEN_HEIGHT; y++) {
        if (y >= 0 && y < SCREEN_HEIGHT)
            e->data[y * SCREEN_WIDTH + x] = FLOOR_COLOR;
    }
}

// Détermine la couleur du mur en fonction du numéro de texture
int get_wall_color(int mapX, int mapY, int side)
{
    int color;

    switch (worldMap[mapX][mapY])
    {
        case 1: color = 0xFFD5F8; break; // Red
        case 2: color = 0xFFB7F4; break; // Green
        case 3: color = 0xFD98ED; break; // Blue
        case 4: color = 0xFD75E8; break; // White
        default: color = 0xFC4AE0; break; // Yellow
    }
    if (side == 1)
        color /= 0.2;
    return (color);
}

// Fonction principale de rendu
int render_scene(t_env *e)
{
    int x = 0;

    while (x < SCREEN_WIDTH)
    {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = e->dirX + e->planeX * cameraX;
        double rayDirY = e->dirY + e->planeY * cameraX;
        int mapX = (int)e->posX;
        int mapY = (int)e->posY;

        double sideDistX, sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        int stepX, stepY, side;
        calculate_step_and_side_dist(e, rayDirX, rayDirY, &stepX, &stepY, &sideDistX, &sideDistY, mapX, mapY);
        perform_dda(e, &mapX, &mapY, &sideDistX, &sideDistY, deltaDistX, deltaDistY, stepX, stepY, &side);
        double perpWallDist = (side == 0)
            ? (mapX - e->posX + (1 - stepX) / 2) / rayDirX
            : (mapY - e->posY + (1 - stepY) / 2) / rayDirY;
        int lineHeight, drawStart, drawEnd;
        calculate_line_positions(e, &drawStart, &drawEnd, perpWallDist, &lineHeight);
        draw_ceiling_and_floor(e, x, drawStart, drawEnd);
        int color = get_wall_color(mapX, mapY, side);
        draw_vertical_line(e, x, drawStart, drawEnd, color);
        x++;
    }
    draw_minimap(e);
    mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
    return (0);
}



int	main(void)
{
    t_env	e;

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
    e.mapHeight = MAP_HEIGHT;  // Correction ici
    e.mapWidth = MAP_WIDTH;    // Correction ici
    mlx_loop_hook(e.mlx, &render_scene, &e);
    mlx_hook(e.win, 2, 1L << 0, &key_press, &e);
    mlx_loop(e.mlx);
    return (0);
}

