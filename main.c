#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>


#define WIDTH 1000
#define HEIGHT 800

#define SKY_COLOR 0x87CEEB   // Light Blue Sky
#define FLOOR_COLOR 0x8B4513 // Brown Earth

typedef struct s_vars{
	void *mlx;
	void *win;
	void *img;
	char *data;
	int bpp;
	int line_len;
	int endian;
}	t_vars;


int	close(int keycode, t_vars *vars)
{
	vars = NULL;
	if (keycode == 53) // ESC
		exit(0);
	return (0);
}

void draw_pixel(t_vars *vars, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	char *dst = vars->data + (y * vars->line_len + x * (vars->bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_background(t_vars *vars)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		int color = (y < HEIGHT / 2) ? SKY_COLOR : FLOOR_COLOR;
		for (int x = 0; x < WIDTH; x++)
		{
			draw_pixel(vars, x, y, color);
		}
	}
}

int	main(void)
{
	t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, close, NULL);
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.data = mlx_get_data_addr(vars.img, &vars.bpp, &vars.line_len, &vars.endian);

	draw_background(&vars);

	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_loop(vars.mlx);
}
