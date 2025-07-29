#include "../cub.h"

#define FOV 60
#define STEP 5
#define AREA 60

char *map[] = {
    "1111111",
    "1100101",
    "1001111",
    "100N011",
    "1111111",
    NULL
};


typedef struct s_ray
{
	double	x;
	double	y;
	double	angle;
	int		lentgh_wall;
	int 	color;
	int 	wieght;
}	t_ray;

void draw_rect(void *mlx, void *win, t_ray ray)
{
    int i = 0;
    while (i < ray.lentgh_wall)
    {
        int j = 0;
        while (j < ray.wieght)
        {
            mlx_pixel_put(mlx, win, (ray.x + j) / WIDTH, (ray.y + i) / HEIGHT, ray.color);
            j++;
        }
        i++;
    }
}

void	ft_ray(t_game game, t_ray *ray)
{
	double	dx;
	double	dy;
	int		x_ray;
	int		y_ray;
	char	hit = 0;
	int		lentgh_wall;

	dx = cos(ray->angle) * STEP;
	dy = sin(ray->angle) * STEP;
	lentgh_wall = 0;

	while (!hit)
	{
		x_ray += dx;
		y_ray += dy;
		lentgh_wall += STEP;
		if (x_ray < 0 || x_ray >= WIDTH || y_ray < 0 || y_ray >= HEIGHT || game.vars.map[y_ray / AREA][x_ray / AREA] == '1')
		{
			hit = 1;
			continue ;
		}
	}
}


void	draw_ray(t_game game)
{
	int		i;
	t_ray	ray;

	ray.color = 0xFFFFFF;
	ray.wieght = 5;
	i = 0;
	while (i < FOV)
	{
		double angle = game.player.angle - (FOV / 2) + i;
		ray.angle = angle;
		ray.x = game.player.x;
		ray.y = game.player.y;
		ft_ray(game, &ray);
		ray.y = 180;
		draw_rect(game.vars.mlx, game.vars.win, ray);
		i++;
	}
}

int	close_window(t_game *game)
{
	game = NULL;
	exit(0);
	return (0);
}



// void	draw_small_map(t_game *game)
// {
// 	int i, j;

// 	i = j = 0;
// 	while (j < 8)
// 	{
// 		while (i < 8)
// 		{
// 			if (map[j][i] == '1')
// 				draw_squar(game->vars.mlx, game->vars.win, i * 5, j * 5, 5);
// 			i++;
// 		}
// 		j++;
// 		i = 0;
// 	}
// }

int	main(void)
{
	t_game	game;

	
	game.player.angle = 0;
	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, WIDTH, HEIGHT, "Raycasting Engine");
	game.vars.img = mlx_new_image(game.vars.mlx, WIDTH, HEIGHT);
	game.vars.addr = mlx_get_data_addr(game.vars.img, &game.vars.bits_per_pixel,
		&game.vars.line_length, &game.vars.endian);
	draw_small_map(&game);

	mlx_hook(game.vars.win, 17, 1L<<17, close_window, &game);

	mlx_loop(game.vars.mlx);
	return (0);
}