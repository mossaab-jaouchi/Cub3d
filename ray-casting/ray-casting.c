#include "../cub.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FOV         60
#define SPEED       5
#define ROT_SPEED   0.05

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
	"11111111111111111111",
	"10000000000000000001",
	"10110000000000000001",
	"10000000000000000001",
	"10110000000000000001",
	"10010000000000000001",
	"11110000000000000001",
	"10000000000000000001",
	"10110000000000000001",
	"10100000000000000001",
	"10101101001111111001",
	"10100001000000000001",
	"10111111101111111101",
	"10000000100000000001",
	"10111110111111111001",
	"10100010000000001001",
	"10101010111111101001",
	"10001000000000001001",
	"10N11111111111111111",
	"11111111111111111111",
	NULL
};


// -------- STRUCTS --------

typedef struct s_ray {
	double x, y;
	double length;
} t_ray;

int rgb_to_int(int r, int g, int b)
{
	return (r << 16) | (g << 8) | b;
}

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

void    draw_ceiling(t_img *img, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel_to_image(img, x, y, color);
			x++;
		}
		y++;
	}
}
void    draw_floor(t_img *img, int color)
{
	int x;
	int y;

	x = 0;
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel_to_image(img, x, y, color);
			x++;
		}
		y++;
	}
}

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
	draw_vertical_line(&game->img, col, start_y, end_y, 0x783f04);
}

void cast_all_rays(t_game *game)
{
	double angle_step = (FOV * M_PI / 180.0) / WIDTH;
	double start_angle = game->player.angle - (FOV * 0.5 * M_PI / 180.0);

	draw_ceiling(&game->img, rgb_to_int(game->ceiling_color.red, game->ceiling_color.green, game->ceiling_color.blue));
	draw_floor(&game->img, rgb_to_int(game->floor_color.red, game->floor_color.green, game->floor_color.blue));
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

static char	is_out_of_bounds(t_game *game, int x, int y)
{
	if (y < 0 || y >= 20)
		return (1);
	if (x < 0 || x >= 21)
		return (1);
	if (game->vars.map[y][x] == '1')
		return (1);
	return (0);
}

static void	update_player_pos(t_game *game, double x, double y, char signal)
{
	if (signal == '+')
	{
		game->player.x += x;
		game->player.y += y;
	}
	else
	{
		game->player.x -= x;
		game->player.y -= y;
	}
}

char	checke_collision(t_game *game, double mx, double my, char signal)
{
	int		mx_i;
	int		my_i;
	double	new_x;
	double	new_y;

	if (!mx && !my)
		return (0);
	new_x = game->player.x + (signal == '+' ? mx : -mx);
	new_y = game->player.y + (signal == '+' ? my : -my);
	mx_i = (int)floor(new_x / TILE_SIZE);
	my_i = (int)floor(new_y / TILE_SIZE);
	if (is_out_of_bounds(game, mx_i, my_i))
		return (1);
	update_player_pos(game, mx, my, signal);
	clear_image(&game->img);
	cast_all_rays(game);
	return (1);
}



int handle_keypresse(int key, t_tool_move *t)
{
    if (key == KEY_W || key == KEY_UP)        t->key_w = 1;
    else if (key == KEY_S || key == KEY_DOWN)   t->key_s = 1;
    else if (key == KEY_A)   t->key_a = 1;
    else if (key == KEY_D)   t->key_d = 1;
    else if (key == KEY_LEFT) t->key_left = 1;
    else if (key == KEY_RIGHT) t->key_right = 1;
    else if (key == KEY_ESC) exit(0);
    return 0;
}


int handle_keyrelease(int key, t_tool_move *t)
{
    if (key == KEY_W || key == KEY_UP)        t->key_w = 0;
    else if (key == KEY_S || key == KEY_DOWN)   t->key_s = 0;
    else if (key == KEY_A)   t->key_a = 0;
    else if (key == KEY_D)   t->key_d = 0;
    else if (key == KEY_LEFT) t->key_left = 0;
    else if (key == KEY_RIGHT) t->key_right = 0;
    return 0;
}


// -------- INPUT --------
int handle_keypress(t_game *game)
{
	t_tool_move *t = &game->tool_move;
	t->move_x = 0;
	t->move_y = 0;

	if (t->key_w || t->key_s || t->key_a || t->key_d)
	{
		if (t->key_w || t->key_s)
		{
			t->move_x = (cos(t->angle) * SPEED);
			t->move_y = (sin(t->angle) * SPEED);
			t->signal = t->key_w ? '+' : '-';
			checke_collision(game, t->move_x, t->move_y, t->signal);
		}
		if (t->key_a || t->key_d)
		{
			t->move_x = cos(t->angle + M_PI_2) * SPEED;
			t->move_y = sin(t->angle + M_PI_2) * SPEED;
			t->signal = '+';
			checke_collision(game, t->move_x, t->move_y, t->signal);
		}
	}

	if (t->key_left)
		t->angle -= ROT_SPEED;
	if (t->key_right)
		t->angle += ROT_SPEED;
	if (game->player.angle != t->angle)
	{
		game->player.angle = t->angle;
		clear_image(&game->img);
		cast_all_rays(game);
	}
	return 0;
}


// int handle_keypresse(int key, t_tool_move *tool_move)
// {
// 	if (key == KEY_W || key == KEY_UP)
// 	{
// 		tool_move->move_x = cos(tool_move->angle) * SPEED;
// 		tool_move->move_y = sin(tool_move->angle) * SPEED;
// 		tool_move->signal = '+';
// 	}
// 	else if (key == KEY_S || key == KEY_DOWN)
// 	{
// 		tool_move->move_x = cos(tool_move->angle) * SPEED;
// 		tool_move->move_y = sin(tool_move->angle) * SPEED;
// 		tool_move->signal = '-';
// 	}
// 	else if (key == KEY_A)
// 	{
// 		tool_move->move_x = cos(tool_move->angle - M_PI_2) * SPEED;
// 		tool_move->move_y = sin(tool_move->angle - M_PI_2) * SPEED;
// 		tool_move->signal = '+';
// 	}
// 	else if (key == KEY_D)
// 	{
// 		tool_move->move_x = cos(tool_move->angle + M_PI_2) * SPEED;
// 		tool_move->move_y = sin(tool_move->angle + M_PI_2) * SPEED;
// 		tool_move->signal = '+';			
// 	}
// 	if (key == KEY_LEFT)
// 		tool_move->angle -= ROT_SPEED;
// 	if (key == KEY_RIGHT)
// 		tool_move->angle += ROT_SPEED;
// 	if (key == KEY_ESC)
// 		exit(0);
// 	return 1;
// }


// -------- MAIN --------
int main(void)
{
	t_game		game;

	memset(&game, 0, sizeof(t_game));
	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, WIDTH, HEIGHT, "Raycasting Engine");

	game.ceiling_color.red = 200;
	game.ceiling_color.green = 220;
	game.ceiling_color.blue = 255;
	game.floor_color.red = 200;
	game.floor_color.green = 255;
	game.floor_color.blue = 200;
	game.vars.map = map;
	game.player.x = 3 * TILE_SIZE + TILE_SIZE / 2;
	game.player.y = 3 * TILE_SIZE + TILE_SIZE / 2;
	game.player.angle = 0;

	game.tool_move.move_x = 0;
	game.tool_move.move_y = 0;
	game.tool_move.signal = 0;
	game.tool_move.angle = game.player.angle;

	game.img.img = mlx_new_image(game.vars.mlx, WIDTH, HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.line_length, &game.img.endian);

	cast_all_rays(&game);
	// mlx_hook(game.vars.win, 2, 0, handle_keypresse, &game.tool_move);
	// mlx_loop_hook(game.vars.mlx, handle_keypress, &game);
	mlx_hook(game.vars.win, 2, 0, handle_keypresse, &game.tool_move);
	mlx_hook(game.vars.win, 3, 0, handle_keyrelease, &game.tool_move);
	mlx_loop_hook(game.vars.mlx, handle_keypress, &game);

	mlx_loop(game.vars.mlx);
	return 0;
}
