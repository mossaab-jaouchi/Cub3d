/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:55:05 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:06:59 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char    stored_path_variable1(t_info_cub *info_cub, char **matrex)
{
    if (!ft_strcmp("WE", matrex[0]) && !info_cub->wall_west)
    {
        info_cub->wall_west = ft_strdup(matrex[1]);
        if (!info_cub->wall_west)
            return (1);
        return (0);
    }
    if (!ft_strcmp("EA", matrex[0]) && !info_cub->wall_east)
    {
        info_cub->wall_east= ft_strdup(matrex[1]);
        if (!info_cub->wall_east)
            return (1);
        return (0);
    }
    return (1);
}

char    stored_path_variable(t_info_cub *info_cub, char **matrex)
{
    if (!ft_strcmp("NO", matrex[0]) && !info_cub->wall_north)
    {
        info_cub->wall_north = ft_strdup(matrex[1]);
        if (!info_cub->wall_north)
            return (1);
        return (0);
    }
    if (!ft_strcmp("SO", matrex[0]) && !info_cub->wall_south)
    {
        info_cub->wall_south = ft_strdup(matrex[1]);
        if (!info_cub->wall_south)
            return (1);
        return (0);
    }
    return (stored_path_variable1(info_cub, matrex));
}

char    parse_paths(t_info_cub *info_cub)
{
    int     i;
    char    **temp;
    char    *string;

    i = 0;
    while (info_cub->parts_file.part_paths[i])
    {
        string = ft_strtrim(info_cub->parts_file.part_paths[i], " \n", 0);
        temp = split_in_two_parts(string, " ");
        if (!temp)
            return (free(string), 1);
        if (stored_path_variable(info_cub, temp))
            return (free_matrex(temp), free(string), 1);
        free_matrex(temp);
        free(string);
        i++;
    }
    return (0);
}
