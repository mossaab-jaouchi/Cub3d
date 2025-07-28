/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_parsing_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:14:54 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/28 15:41:08 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void get_start_end(int *end, int *start, char *line)
{
    int start_pos;
    int end_pos;

    start_pos = 0;
    end_pos = ft_strlen(line) - 1;
    while (line[start_pos] && is_whitespace(line[start_pos]))
        start_pos++;
    if (!end_pos || end_pos == start_pos)
    {
         *end = end_pos;
        *start = start_pos;
        return ;
    }
    while (line[end_pos] && is_whitespace(line[end_pos]))
        end_pos--;
    *end = end_pos;
    *start = start_pos;
}

char    check_with_hiegth_map(char *line, int index, int length_map)
{
    int i;
    int end;
    int start;

    i = 0;
    while (line[i])
    {
        if (index == 0 || (length_map - 1) == index)
        {
            if (!(is_whitespace(line[i]) || line[i] == '1'))
                return (1);
        }
        i++;
    }
    get_start_end(&end, &start, line);
    if (!((line[end] == '1' && line[start] == '1')))
        return (1);
    return (0);
}

char    check_empty_space_map_up(char *line, char **map, int index, size_t i)
{
    if (index - 1 >= 0)
    {
        if (i > ft_strlen(map[index - 1]) - 1)
            return (1);
        else
            if (is_whitespace(map[index - 1][i]))
                return (1);
    }
    if (i > 0)
        if (is_whitespace(line[i - 1]))
            return (1);
    return (0);
}

char    check_empty_space_map(char *line, char **map, int index, int length_map)
{
    size_t i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '0' || is_player_char(line[i]))
        {
            if (index + 1 <= length_map - 1)
            {
                if (i > ft_strlen(map[index + 1]) - 1)
                    return (1);
                else
                    if (is_whitespace(map[index + 1][i]))
                        return (1);
            }
            if (i + 1 <= (ft_strlen(line) - 1))
                if (is_whitespace(line[i + 1]))
                    return (1);
            if (check_empty_space_map_up(line, map, index, i))
                return (1);
        }
        i++;
    }
    return (0);
}

char    base_parsing_map(char *line, char **map, int index, int length_map)
{
    if (count_char(line, '\n') > 1 || !ft_strcmp(line, "\n"))
        return (1);
    if (check_whitespace(line))
        return (0);
    if (check_correct_char(line))
        return (1);
    if (check_with_hiegth_map(line, index, length_map))
        return (1);
    if (check_empty_space_map(line, map, index, length_map))
        return (1);
    return (0);
}