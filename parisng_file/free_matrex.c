/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:33:11 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:06:20 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

short	free_matrex(char **matrex)
{
	int	i;

	i = 0;
	if (!matrex)
		return (-1);
	while (matrex[i])
	{
		free(matrex[i]);
		i++;
	}
	free(matrex);
	matrex = NULL;
	return (-1);
}
