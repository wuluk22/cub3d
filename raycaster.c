#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
//#include "cub3d/minilibx_opengl_20191021/mlx.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

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

typedef struct {
    void *mlx;
    void *win;
    void *img;
    int *data;
    int bpp;
    int sizeline;
    int endian;
    double posX, posY;  // Add player position
    double dirX, dirY;  // Add player direction
    double planeX, planeY; // Add camera plane
} t_env;

int key_press(int keycode, t_env *e)
{
    double moveSpeed = 0.1;  // Adjust speed as needed
    double rotSpeed = 0.05;  // Adjust rotation speed as needed
    double oldDirX, oldPlaneX;

    if (keycode == 126)
    {  // W key for forward movement
        if (worldMap[(int)(e->posX + e->dirX * moveSpeed)][(int)(e->posY)] == 0) e->posX += e->dirX * moveSpeed;
        if (worldMap[(int)(e->posX)][(int)(e->posY + e->dirY * moveSpeed)] == 0) e->posY += e->dirY * moveSpeed;
    }
    if (keycode == 125)
    {  // S key for backward movement
        if (worldMap[(int)(e->posX - e->dirX * moveSpeed)][(int)(e->posY)] == 0) e->posX -= e->dirX * moveSpeed;
        if (worldMap[(int)(e->posX)][(int)(e->posY - e->dirY * moveSpeed)] == 0) e->posY -= e->dirY * moveSpeed;
    }
    if (keycode == 124)
    {  // D key for right rotation
        oldDirX = e->dirX;
        e->dirX = e->dirX * cos(-rotSpeed) - e->dirY * sin(-rotSpeed);
        e->dirY = oldDirX * sin(-rotSpeed) + e->dirY * cos(-rotSpeed);
        oldPlaneX = e->planeX;
        e->planeX = e->planeX * cos(-rotSpeed) - e->planeY * sin(-rotSpeed);
        e->planeY = oldPlaneX * sin(-rotSpeed) + e->planeY * cos(-rotSpeed);
    }
    if (keycode == 123)
    {  // A key for left rotation
        oldDirX = e->dirX;
        e->dirX = e->dirX * cos(rotSpeed) - e->dirY * sin(rotSpeed);
        e->dirY = oldDirX * sin(rotSpeed) + e->dirY * cos(rotSpeed);
        oldPlaneX = e->planeX;
        e->planeX = e->planeX * cos(rotSpeed) - e->planeY * sin(rotSpeed);
        e->planeY = oldPlaneX * sin(rotSpeed) + e->planeY * cos(rotSpeed);
    }
    return 0;
}


void draw_vertical_line(t_env *e, int x, int start, int end, int color)
{
    int i;

    for (i = start; i < end; i++) {
        e->data[i * SCREEN_WIDTH + x] = color;
    }
}



int render_scene(t_env *e)
{
    int x;
    int color;
    double posX = 22, posY = 12; // Replace these with global or shared variables
    double dirX = -1, dirY = 0;
    double planeX = 0, planeY = 0.66;

    mlx_clear_window(e->mlx, e->win);
    
    for (x = 0; x < SCREEN_WIDTH; x++)
    {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;
        int mapX = (int)posX;
        int mapY = (int)posY;
        double sideDistX;
        double sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;
        int stepX, stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT)
            drawEnd = SCREEN_HEIGHT - 1;

        switch (worldMap[mapX][mapY])
        {
            case 1: color = 0xFF0000; break; // red
            case 2: color = 0x00FF00; break; // green
            case 3: color = 0x0000FF; break; // blue
            case 4: color = 0xFFFFFF; break; // white
            default: color = 0xFFFF00; break; // yellow
        }

        if (side == 1) color /= 2;

        draw_vertical_line(e, x, drawStart, drawEnd, color);
    }

    mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
    return 0; // Continue the loop
}


int main(void)
{
    t_env e;

    e.mlx = mlx_init();
    e.win = mlx_new_window(e.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
    e.img = mlx_new_image(e.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    e.data = (int *)mlx_get_data_addr(e.img, &e.bpp, &e.sizeline, &e.endian);

    // Initialize player position and direction
    e.posX = 22;
    e.posY = 12;
    e.dirX = -1;
    e.dirY = 0;
    e.planeX = 0;
    e.planeY = 0.66;

    // Set up key press event handler
    mlx_key_hook(e.win, key_press, &e);

    // Set up rendering function
    mlx_loop_hook(e.mlx, (int(*)(void *))render_scene, &e);

    // Start the event loop
    mlx_loop(e.mlx);

    // Clean up (this will never be reached in the current loop)
    mlx_destroy_image(e.mlx, e.img);
    mlx_destroy_window(e.mlx, e.win);
    free(e.mlx);

    return 0;
}
