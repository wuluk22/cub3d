#include "includes/cub3D.h"

int key_press(int keycode, t_env *e)
{
    if (keycode == KEY_ESC)
        exit(0);
    e->keys[keycode] = 1; // Marque la touche comme enfoncée
    printf("Key pressed: %d\n", keycode);
    return (0);
}

int key_release(int keycode, t_env *e)
{
    e->keys[keycode] = 0; // Marque la touche comme relâchée
    printf("Key released: %d\n", keycode);
    return (0);
}


void move_player(t_env *e)
{
    double moveSpeed = 0.05;  // Vitesse de déplacement
    double rotSpeed = 0.03;   // Vitesse de rotation

    //printf("Player position: (%f, %f)\n", e->posX, e->posY);
    //printf("Player direction: (%f, %f)\n", e->dirX, e->dirY);
    //printf("Plane: (%f, %f)\n", e->planeX, e->planeY);
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

    if (e->keys[KEY_LEFT] && !e->keys[KEY_RIGHT])
    {
    // Vérifier qu'il n'y a pas de mur trop proche sur la gauche (exemple)
        if (worldMap[(int)(e->posX - e->dirY * moveSpeed)][(int)(e->posY + e->dirX * moveSpeed)] == 0)
        {
            printf("Before rotation: dirX = %f, dirY = %f, planeX = %f, planeY = %f\n", e->dirX, e->dirY, e->planeX, e->planeY);
            double oldDirX = e->dirX;
            e->dirX = e->dirX * cos(rotSpeed) - e->dirY * sin(rotSpeed);
            e->dirY = oldDirX * sin(rotSpeed) + e->dirY * cos(rotSpeed);

            double oldPlaneX = e->planeX;
            e->planeX = e->planeX * cos(rotSpeed) - e->planeY * sin(rotSpeed);
            e->planeY = oldPlaneX * sin(rotSpeed) + e->planeY * cos(rotSpeed);
            printf("After rotation: dirX = %f, dirY = %f, planeX = %f, planeY = %f\n", e->dirX, e->dirY, e->planeX, e->planeY);
            printf("key value %d\n", e->keys[KEY_LEFT]);
        }
    }

    if (e->keys[KEY_RIGHT] && !e->keys[KEY_LEFT])
    {
    // Vérifier qu'il n'y a pas de mur trop proche sur la droite (exemple)
        if (worldMap[(int)(e->posX + e->dirY * moveSpeed)][(int)(e->posY - e->dirX * moveSpeed)] == 0)
        {
            printf("Before rotation: dirX = %f, dirY = %f, planeX = %f, planeY = %f\n", e->dirX, e->dirY, e->planeX, e->planeY);
            double oldDirX = e->dirX;
            e->dirX = e->dirX * cos(-rotSpeed) - e->dirY * sin(-rotSpeed);
            e->dirY = oldDirX * sin(-rotSpeed) + e->dirY * cos(-rotSpeed);

            double oldPlaneX = e->planeX;
            e->planeX = e->planeX * cos(-rotSpeed) - e->planeY * sin(-rotSpeed);
            e->planeY = oldPlaneX * sin(-rotSpeed) + e->planeY * cos(-rotSpeed);
            printf("After rotation: dirX = %f, dirY = %f, planeX = %f, planeY = %f\n", e->dirX, e->dirY, e->planeX, e->planeY);
            printf("key value %d\n", e->keys[KEY_RIGHT]);
        }
    }

}

