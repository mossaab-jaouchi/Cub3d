#include "../cub.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FOV         60
#define SPEED       15
#define ROT_SPEED   0.3

#define KEY_ESC     53
#define KEY_W       13
#define KEY_A       0
#define KEY_S       1
#define KEY_D       2
#define KEY_LEFT    123
#define KEY_RIGHT   124
#define KEY_UP      126
#define KEY_DOWN    125

char *map[] = {
    "1111111",
    "1101111",
    "1000001",
    "100N011",
    "1111111",
    NULL
};

// -------- STRUCTS --------

typedef struct s_ray {
    double x, y;
    double length;
} t_ray;

// -------- UTILS --------
void put_pixel_to_image(t_img *img, int x, int y, int color)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    char *dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

void clear_image(t_img *img)
{
    memset(img->addr, 0, WIDTH * HEIGHT * (img->bpp / 8));
}

// -------- DRAWING --------
void draw_vertical_line(t_img *img, int x, int start_y, int end_y, int color)
{
    if (start_y < 0) start_y = 0;
    if (end_y >= HEIGHT) end_y = HEIGHT - 1;

    for (int y = start_y; y <= end_y; y++)
        put_pixel_to_image(img, x, y, color);
}

void draw_square(t_game *game, int x, int y, int size, int color)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            put_pixel_to_image(&game->img, x + j, y + i, color);
}

void draw_mini_map(t_game *game)
{
    int scale = 10;
    for (int y = 0; game->vars.map[y]; y++)
    {
        for (int x = 0; game->vars.map[y][x]; x++)
        {
            int color = (game->vars.map[y][x] == '1') ? 0x888888 : 0x222222;
            draw_square(game, x * scale, y * scale, scale, color);
        }
    }
    draw_square(game, (int)(game->player.x / TILE_SIZE) * scale,
                      (int)(game->player.y / TILE_SIZE) * scale, scale, 0x00FF00);
}

// -------- RAYCASTING --------
void execute_ray(t_game *game, double angle, t_ray *ray)
{
    double ray_x = cos(angle);
    double ray_y = sin(angle);

    double pos_x = game->player.x / TILE_SIZE;
    double pos_y = game->player.y / TILE_SIZE;

    int map_x = (int)pos_x;
    int map_y = (int)pos_y;

    double delta_x = fabs(1 / ray_x);
    double delta_y = fabs(1 / ray_y);

    int step_x = (ray_x < 0) ? -1 : 1;
    int step_y = (ray_y < 0) ? -1 : 1;

    double side_x = (ray_x < 0) ? (pos_x - map_x) * delta_x : (map_x + 1.0 - pos_x) * delta_x;
    double side_y = (ray_y < 0) ? (pos_y - map_y) * delta_y : (map_y + 1.0 - pos_y) * delta_y;

    int hit = 0, side;

    while (!hit)
    {
        if (side_x < side_y)
        {
            side_x += delta_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_y += delta_y;
            map_y += step_y;
            side = 1;
        }
        if (game->vars.map[map_y][map_x] == '1')
            hit = 1;
    }

    double dist = (side == 0) ? (side_x - delta_x) : (side_y - delta_y);
    ray->length = dist * TILE_SIZE;
}

void draw_ray_column(t_game *game, double ray_length, int col, double angle_diff)
{
    double corrected = ray_length * cos(angle_diff);
    double wall_h = (TILE_SIZE * HEIGHT) / corrected;

    if (wall_h > HEIGHT) wall_h = HEIGHT;

    int start_y = (HEIGHT / 2) - (wall_h / 2);
    int end_y = (HEIGHT / 2) + (wall_h / 2);
    draw_vertical_line(&game->img, col, start_y, end_y, 0xFFFFFF);
}

void cast_all_rays(t_game *game)
{
    double angle_step = (FOV * M_PI / 180.0) / WIDTH;
    double start_angle = game->player.angle - (FOV * 0.5 * M_PI / 180.0);

    for (int col = 0; col < WIDTH; col++)
    {
        double ray_angle = start_angle + col * angle_step;
        t_ray ray;
        execute_ray(game, ray_angle, &ray);
        draw_ray_column(game, ray.length, col, ray_angle - game->player.angle);
    }
    draw_mini_map(game);
    mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
}

char    checke_collision(t_game *game, double move_x, double move_y, char signal)
{
    if (!move_x && !move_y)
        return (0);
    if (signal == '+')
    {
        printf("Player position: (%d, %d)\n", (int)floor((game->player.y + move_y) / TILE_SIZE), (int)floor((game->player.x + move_x) / TILE_SIZE));
        if ((game->player.y + move_y) < 0 || (game->player.y + move_y) >= HEIGHT)
            return (1);
        if ((game->player.x + move_x) < 0 || (game->player.x + move_x) >= WIDTH || (game->vars.map[(int)floor((game->player.y + move_y) / TILE_SIZE)][(int)floor((game->player.x + move_x) / TILE_SIZE)] == '1'))
            return (1);
        game->player.x += move_x;
        game->player.y += move_y;
    }
    else if (signal == '-')
    {
        printf("Player position: (%.2f, %.2f)\n", game->player.x + move_x, game->player.y + move_y);
        if ((game->player.y - move_y) < 0 || (game->player.y - move_y) >= HEIGHT)
            return (1);
        if ((game->player.x - move_x) < 0 || (game->player.x - move_x) >= WIDTH || (game->vars.map[(int)floor((game->player.y - move_y) / TILE_SIZE)][(int)floor((game->player.x - move_x) / TILE_SIZE)] == '1'))
            return (1);
        game->player.x -= move_x;
        game->player.y -= move_y;
    }
    clear_image(&game->img);
    cast_all_rays(game);
    return (1);
}

// -------- INPUT --------
int handle_keypress(int key, t_game *game)
{
    double  move_x = 0;
    double  move_y = 0;
    char    signal;
    double  angle;

    signal = 0;
    angle = game->player.angle;
    if (key == KEY_W || key == KEY_UP)
    {
        move_x = cos(game->player.angle) * SPEED;
        move_y = sin(game->player.angle) * SPEED;
        signal = '+';
    }
    else if (key == KEY_S || key == KEY_DOWN)
    {
        move_x = cos(game->player.angle) * SPEED;
        move_y = sin(game->player.angle) * SPEED;
        signal = '-';
    }
    else if (key == KEY_A)
    {
        move_x = cos(game->player.angle - M_PI_2) * SPEED;
        move_y = sin(game->player.angle - M_PI_2) * SPEED;
        signal = '+';
    }
    else if (key == KEY_D)
    {
        move_x = cos(game->player.angle + M_PI_2) * SPEED;
        move_y = sin(game->player.angle + M_PI_2) * SPEED;
        signal = '+';
    }
    if (key == KEY_LEFT)
        angle -= ROT_SPEED;
    if (key == KEY_RIGHT)
        angle += ROT_SPEED;
    if (key == KEY_ESC)
        exit(0);
    checke_collision(game, move_x, move_y, signal);
    if (angle != game->player.angle)
    {
        game->player.angle = angle;
        clear_image(&game->img);
        cast_all_rays(game);
    }
    return (0);
}

// -------- MAIN --------
int main(void)
{
    t_game game;

    game.vars.map = map;
    game.player.x = 3 * TILE_SIZE + TILE_SIZE / 2;
    game.player.y = 3 * TILE_SIZE + TILE_SIZE / 2;
    game.player.angle = 0;

    game.vars.mlx = mlx_init();
    game.vars.win = mlx_new_window(game.vars.mlx, WIDTH, HEIGHT, "Raycasting Engine");

    game.img.img = mlx_new_image(game.vars.mlx, WIDTH, HEIGHT);
    game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.line_length, &game.img.endian);

    cast_all_rays(&game);
    mlx_hook(game.vars.win, 2, 0, handle_keypress, &game);
    mlx_loop(game.vars.mlx);
    return 0;
}
