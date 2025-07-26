/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:02:24 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:07:26 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char    trim_matrix(char ***part_colors, char *sep)
{
    int i = 0;
    char **matrex;

    matrex = malloc(sizeof(char *) * (count_matrex(*part_colors) + 1));
    if (!matrex)
        return (1);
    while ((*part_colors)[i])
    {
        matrex[i] = ft_strtrim((*part_colors)[i], sep, 0);
        if (!matrex[i])
            return (free_matrex(matrex), 1);
        i++;
    }
    matrex[i] = NULL;
    free_matrex(*part_colors);
    *part_colors = matrex;
    return (0);
}
