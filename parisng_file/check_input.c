/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:49:38 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:09:56 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	count_matrex(char **matrex)
{
	int	i;

	i = 0;
	if (!matrex)
		return (0);
	while (matrex[i])
		i++;
	return (i);
}

char	check_input(int argc, char **argv)
{
	char	**matrex;
	int		i;

	if (argc == 1 || argc > 2)
		return (ft_putendl_fd("Error\nArgs not valid `'program' 'name mape'`", 2));
	matrex = ft_split(argv[1], '.');
	i = count_matrex(matrex);
	if (!i)
		return (free_matrex(matrex), ft_putendl_fd("Error\nFiled malloc or empty string", 2));
	if (ft_strcmp(matrex[i - 1], "cub"))
		return (free_matrex(matrex), ft_putendl_fd("Error\nYou should be write '.cub' !!", 2));
	free_matrex(matrex);
	return (0);
}
