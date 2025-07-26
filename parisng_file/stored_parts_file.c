/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stored_parts_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:55:18 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:07:22 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char    stored_part_paths(char **file, t_part_file *part_file)
{
    part_file->part_paths = ft_calloc(5 , sizeof(char *));
    if (!part_file->part_paths)
        return (free_matrex(file), -1);
    if (get_path_color(file, part_file->part_paths, 0, 4))
        return (-1);
    return (0);
}

char    stored_part_colors(char **file, t_part_file *part_file)
{
    part_file->part_colors = ft_calloc(3 , sizeof(char *));
    if (!part_file->part_colors)
        return (free_matrex(file), -1);
    if (get_path_color(file, part_file->part_colors, 5, 2))
        return (-1);
    return (0);
}

char    stored_part_map(char **file, t_part_file *part_file)
{
    int length_map;

    length_map = get_length_map(file, 7);
    if (!length_map)
        return (-1);
    part_file->part_map = ft_calloc((length_map + 1) , sizeof(char *));
    if (!part_file->part_map)
        return (-1);
    if (get_clean_map(file, part_file->part_map, 7, length_map))
        return (-1);
    return (0);
}

char    storted_parts(char **file, t_part_file *part_file)
{
    int error;

    if (!file)
        return (ft_putendl_fd("Error\nEmpty file!!", 2), -1);
    error = stored_part_paths(file, part_file);
    if (error)
        return (free_matrex(file), free_matrex(part_file->part_paths),ft_putendl_fd("Error\nAllocation patrt paths failed !!", 2), -1);
    error = stored_part_colors(file, part_file);
    if (error)
        return (free_matrex(file), free_matrex(part_file->part_paths), free_matrex(part_file->part_colors), ft_putendl_fd("Error\nAllocation patrt colors failed !!", 2),-1);
    error = stored_part_map(file, part_file);
    if (error)
        return (free_matrex(file), free_matrex(part_file->part_paths), free_matrex(part_file->part_colors), ft_putendl_fd("Error\nAllocation patrt map failed !!", 2),-1);
    free_matrex(file);
    return (0);
}
