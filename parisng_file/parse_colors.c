/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:09:28 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:06:49 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char    is_colors(char *str)
{
    return (!ft_strcmp(str, "C") || !ft_strcmp(str, "F"));
}

char    stored_struct_numbers(t_info_cub *info_cub, char *str, char **colors)
{
    if (!ft_strcmp("C", str))
    {
        info_cub->ceiling.red = ft_atoi(colors[0]);
        if (info_cub->ceiling.red < 0 || info_cub->ceiling.red > 255)
            return (1);
        info_cub->ceiling.green = ft_atoi(colors[1]);
        if (info_cub->ceiling.green < 0 || info_cub->ceiling.green > 255)
            return (1);
        info_cub->ceiling.blue = ft_atoi(colors[2]);
        if (info_cub->ceiling.blue < 0 || info_cub->ceiling.blue > 255)
            return (1);
    }
    if (!ft_strcmp("F", str))
    {
        info_cub->floor.red = ft_atoi(colors[0]);
        if (info_cub->floor.red < 0 || info_cub->floor.red > 255)
            return (1);
        info_cub->floor.green = ft_atoi(colors[1]);
        if (info_cub->floor.green < 0 || info_cub->floor.green > 255)
            return (1);
        info_cub->floor.blue = ft_atoi(colors[2]);
        if (info_cub->floor.blue < 0 || info_cub->floor.blue > 255)
            return (1);
    }
    return (0);
}

char    parse_colors(t_info_cub *info_cub)
{
    char    **temp;
    char    *string;
    char    **numbers;
    int     i;

    numbers = NULL;
    i = 0;
    while (info_cub->parts_file.part_colors[i])
    {
        string = ft_strtrim(info_cub->parts_file.part_colors[i], " \n", 0);
        temp = split_in_two_parts(string, " ");
        if (!temp)
            return (free(string), 1);
        if (parse_string_colors(temp, &numbers))
            return (free(string), free_matrex(temp), 1);
        if (stored_struct_numbers(info_cub, temp[0], numbers))
            return (free(string), free_matrex(temp), free_matrex(numbers), 1);
        i++;
        free(string);
        free_matrex(temp);
        free_matrex(numbers);
    }
    return (0);
}
