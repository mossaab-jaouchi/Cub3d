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
	"10101100001111111001",
	"10100000000000000001",
	"10111110001111111101",
	"10000000000000000001",
	"10111110001111111001",
	"10100010000000001001",
	"10101010001111101001",
	"10001000000000001001",
	"10N11110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111110001111111111",
	"11111111111111111111",
	NULL
};



typedef struct s_ray {
	double x, y;
	double length;
} t_ray;

int rgb_to_int(int r, int g, int b)
{
	return (r << 16) | (g << 8) | b;
}

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

void draw_vertical_line(t_img *img, int x, int start_y, int end_y, t_img *color)
{
	if (start_y < 0) start_y = 0;
	if (end_y >= HEIGHT) end_y = HEIGHT - 1;
	color->bpp = 32; // Assuming 32 bits per pixel
	for (int y = start_y; y <= end_y; y++)
	{
		// unsigned int pixel = *(unsigned int *)(color->addr + (y * color->line_length + x * (color->bpp / 8)));
		put_pixel_to_image(img, x, y, 0x791d1d);
	}
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
	draw_vertical_line(&game->img, col, start_y, end_y, &game->wall_texture);
}

void cast_all_rays(t_game *game)
{
	double	angle_step = (FOV * M_PI / 180.0) / WIDTH;
	double	start_angle = game->player.angle - (FOV * 0.5 * M_PI / 180.0);
	int		col = 0;
	t_ray	ray;

	draw_ceiling(&game->img, rgb_to_int(game->ceiling_color.red, game->ceiling_color.green, game->ceiling_color.blue));
	draw_floor(&game->img, rgb_to_int(game->floor_color.red, game->floor_color.green, game->floor_color.blue));
	while (col < WIDTH)
	{
		double ray_angle = start_angle + col * angle_step;
		execute_ray(game, ray_angle, &ray);
		draw_ray_column(game, ray.length, col, ray_angle - game->player.angle);
		col++;
	}
	draw_mini_map(game);
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
}

static char	is_out_of_bounds(t_game *game, int x, int y)
{
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
			t->signal = (t->key_a) ? '-' : '+';
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

#include <mlx.h>
#include <math.h>

void	draw_circle_from_xpm(void *mlx, void *win, char *xpm_path)
{
	int		w, h;
	void	*img;
	char	*addr;
	int		bpp, line_len, endian;
	int		x, y;
	int		cx, cy, radius;

	img = mlx_xpm_file_to_image(mlx, xpm_path, &w, &h);
	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);

	cx = w / 2;
	cy = h / 2;
	radius = (w < h ? w : h) / 2;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			int dx = x - cx;
			int dy = y - cy;
			if (dx * dx + dy * dy <= radius * radius)
			{
				int pixel = *(int *)(addr + y * line_len + x * (bpp / 8));
				mlx_pixel_put(mlx, win, x, y, pixel);
			}
		}
	}
}


void	draw_tilted_wall_xpm(t_game *game, void *xpm_img, int img_w, int img_h, int start_x, int start_y, double angle)
{
	int		x, y;
	char	*src_addr;
	char	*dst_addr;
	int		src_bpp, src_line_len, src_endian;
	int		dst_bpp, dst_line_len, dst_endian;
	int		new_x, new_y;

	src_addr = mlx_get_data_addr(xpm_img, &src_bpp, &src_line_len, &src_endian);
	dst_addr = mlx_get_data_addr(game->img.img, &dst_bpp, &dst_line_len, &dst_endian);

	for (y = 0; y < img_h; y++)
	{
		for (x = 0; x < img_w; x++)
		{
			long int color = (int long)(src_addr + y * src_line_len + x * (src_bpp / 8));
			if (color == 0xFF000000)
				continue;
			
			new_x = (int)(start_x + x + tan(angle) * y);
			new_y = start_y + y;

			if (new_x >= 0 && new_y >= 0 && new_x < WIDTH && new_y < HEIGHT)
				*(unsigned int *)(dst_addr + new_y * dst_line_len + new_x * (dst_bpp / 8)) = color;
		}
	}
}

void copy_partial_image(t_img *src, t_img *dest, int start_x, int width)
{
	for (int y = 0; y < src->height && y < dest->height; y++)
	{
		for (int x = 0; x < width && (start_x + x) < src->width && x < dest->width; x++)
		{
			char *src_px = src->addr + (y * src->line_length + (start_x + x) * (src->bpp / 8));
			char *dst_px = dest->addr + (y * dest->line_length + x * (dest->bpp / 8));
			*(unsigned int *)dst_px = *(unsigned int *)src_px;
		}
	}
}

int key(int key, t_game *game)
{
	game = NULL;
	if (key == KEY_ESC)
		exit(0);
	return 0;
}

int main(void)
{
	t_game		game;
	t_img		img;


	memset(&game, 0, sizeof(t_game));
	memset(&img, 0, sizeof(t_img));
	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, WIDTH, HEIGHT, "Raycasting Engine");

	game.img.img = mlx_new_image(game.vars.mlx, WIDTH, HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.line_length, &game.img.endian);

	game.wall_texture.img = mlx_xpm_file_to_image(game.vars.mlx, "img/texture1.xpm", &game.wall_texture.width, &game.wall_texture.height);
	game.wall_texture.addr = mlx_get_data_addr(game.wall_texture.img, &game.wall_texture.bpp, &game.wall_texture.line_length, &game.wall_texture.endian);

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

	img.width = 300;
	img.height = 60;
	// draw_tilted_wall_xpm(&game, "img/1.xpm", 64, 64, 100, 100, angle);
	cast_all_rays(&game);
	// mlx_hook(game.vars.win, 2, 0, handle_keypresse, &game.tool_move);
	// mlx_loop_hook(game.vars.mlx, handle_keypress, &game);
	mlx_hook(game.vars.win, 2, 0, handle_keypresse, &game.tool_move);
	mlx_hook(game.vars.win, 3, 0, handle_keyrelease, &game.tool_move);
	mlx_loop_hook(game.vars.mlx, handle_keypress, &game);
	mlx_loop(game.vars.mlx);
	return 0;
}
