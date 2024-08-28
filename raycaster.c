#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>

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

typedef struct s_env {
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
}	t_env;

int	key_press(int keycode, t_env *e)
{
    double	moveSpeed = 0.5;
    double	rotSpeed = 0.10;
    double	oldDirX;
    double	oldPlaneX;

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

void	draw_vertical_line(t_env *e, int x, int start, int end, int color)
{
    int	i;

    i = start;
    while (i < end)
    {
        e->data[i * SCREEN_WIDTH + x] = color;
        i++;
    }
}

int	render_scene(t_env *e)
{
    int		x;

    // Clear the image buffer by setting all pixels to black
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        e->data[i] = 0x000000;  // Black color

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        double	cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double	rayDirX = e->dirX + e->planeX * cameraX;
        double	rayDirY = e->dirY + e->planeY * cameraX;
        int		mapX = (int)e->posX;
        int		mapY = (int)e->posY;
        double	sideDistX;
        double	sideDistY;
        double	deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double	deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double	perpWallDist;
        int		stepX;
        int		stepY;
        int		hit = 0;
        int		side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (e->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - e->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (e->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - e->posY) * deltaDistY;
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
            if (worldMap[mapX][mapY] > 0)
                hit = 1;
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

        int color;
        switch (worldMap[mapX][mapY])
        {
            case 1: color = 0xFF0000; break; // Red
            case 2: color = 0x00FF00; break; // Green
            case 3: color = 0x0000FF; break; // Blue
            case 4: color = 0xFFFFFF; break; // White
            default: color = 0xFFFF00; break; // Yellow
        }
        if (side == 1)
            color = color / 2;
        draw_vertical_line(e, x, drawStart, drawEnd, color);
        x++;
    }
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
    mlx_loop_hook(e.mlx, &render_scene, &e);
    mlx_hook(e.win, 2, 1L << 0, &key_press, &e);
    mlx_loop(e.mlx);
    return (0);
}
