/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:00:39 by achamdao          #+#    #+#             */
/*   Updated: 2025/08/04 09:49:40 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void f()
{
    system("leaks cube");
}
void print_matrix(char **matrix)
{
    int i = 0;
    while (matrix[i])
    {
        printf("%s", matrix[i]);
        i++;
    }
}

void    free_info_cub(t_info_cub *info_cube)
{
    free_matrex(info_cube->parts_file.part_paths);
    free_matrex(info_cube->parts_file.part_colors);
    if (!info_cube->map)
        free_matrex(info_cube->parts_file.part_map);
    free_matrex(info_cube->map);
    free(info_cube->wall_east);
    free(info_cube->wall_north);
    free(info_cube->wall_south);
    free(info_cube->wall_west);
}

char    parsing_info(int argc, char **argv, t_info_cub *info_cube)
{
    char    **file;

    if (check_input(argc, argv))
        return (1);
    file = stored_map(argv[1]);
    if(storted_parts(file, &info_cube->parts_file))
        return (1);
    if (parse_paths(info_cube))
        return (free_info_cub(info_cube), ft_putendl_fd("Error\nInvalid path!!", 2), 1);
    if (parse_colors(info_cube))
        return (free_info_cub(info_cube), ft_putendl_fd("Error\nInvalid color!!", 2),  1);
    if (parse_map(info_cube->parts_file.part_map, info_cube))
        return (free_info_cub(info_cube), ft_putendl_fd("Error\nInvalid map!!", 2),  1);
    return (0);
}

int main(int argc, char **argv)
{
    t_info_cub info_cub;
    
    // atexit(f);
    ft_memset(&info_cub, 0, sizeof(info_cub));
    if (parsing_info(argc, argv, &info_cub))
        return (1);
    ft_putendl_fd(info_cub.wall_east, 1);
    ft_putendl_fd(info_cub.wall_west, 1);
    ft_putendl_fd(info_cub.wall_south, 1);
    ft_putendl_fd(info_cub.wall_north, 1);
    printf("C red %d \n", info_cub.ceiling.red);
    printf("C green %d \n", info_cub.ceiling.green);
    printf("C blue %d \n", info_cub.ceiling.blue);
   printf("F red %d \n", info_cub.floor.red);
    printf("F green %d \n", info_cub.floor.green);
    printf("F blue %d \n", info_cub.floor.blue);
    printf("Pos x player %f \n", info_cub.x);
    printf("Pos y player %f \n", info_cub.y);
    print_matrix(info_cub.map);
    free_info_cub(&info_cub);
    return (0);
}
