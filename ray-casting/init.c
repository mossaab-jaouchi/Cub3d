/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:03:18 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/07/29 10:03:26 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_vars(t_vars *vars, t_info_cub info)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Cub3D");
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
		&vars->line_length, &vars->endian);
}

void	init_player(t_player *player, t_info_cub info)
{
	player->x = info.x * TILE_SIZE;
	player->y = info.y * TILE_SIZE;
	if (info.angle == 'N')
		player->angle = 0;
	else if (info.angle == 'E')
		player->angle = M_PI_2;
	else if (info.angle == 'S')
		player->angle = M_PI;
	else if (info.angle == 'W')
		player->angle = 3 * M_PI_2;
	else
		player->angle = 0;
}

void	init_game(t_game *game, t_info_cub info)
{
	init_vars(&game->vars, info);
	init_player(&game->player, info);
}
