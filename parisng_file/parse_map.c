/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:11:16 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:39:58 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char    is_player_char(char c)
{
    return (c == 'W' || c == 'N' || c == 'S' || c == 'E');
}

char    is_char_map(char c)
{
    return (is_whitespace(c) || c == '1' || c == '0');
}

char    check_correct_char(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (!is_char_map(line[i]) && !is_player_char(line[i]))
            return (1);
        i++;
    }
    if (check_whitespace(line))
        return (1);    
    return (0);
}

char    check_player(char *line, int count_player, int index, t_info_cub *s_info_cub)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (is_player_char(line[i]))
        {
            s_info_cub->x = i + 0.5;
            s_info_cub->y = index + 0.5;
            count_player++;
        }
        i++;
    }
    return (count_player);
}

char    parse_map(char **map , t_info_cub *info_cube)
{
    size_t length_line;
    int length_map;
    int count_player;
    int i;

    length_map = count_matrex(map);
    if (!length_map)
        return (1);
    count_player = 0;
    length_line = ft_strlen(map[0]);
    i = 0;
    while (map[i])
    {
        if (base_parsing_map(map[i], map, i, length_map))
            return (1);
        count_player = check_player(map[i], count_player, i, info_cube);
        i++;
    }
    if (count_player != 1)
        return (1);
    info_cube->map = map;
    return (0);
}
