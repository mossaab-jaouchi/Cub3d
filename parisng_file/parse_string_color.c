/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:08:50 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:07:05 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int count_char(char *str, char c)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

char    check_is_number(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (1);
        i++;
    }
    return (0);
}

char    check_number_color(char **matrex)
{
    int i;

    i = 1;
    while (matrex[i])
    {
        if (check_is_number(matrex[i]))
            return (1);
        i++;
    }
    return (0);
}

char    parse_string_colors(char **temp, char ***numbers)
{
    if (!is_colors(temp[0]))
        return (1);
    if (count_word(temp[1], ",") != 3)
        return (1);
    *numbers = new_split(temp[1], ",");
    if (!*numbers)
        return (1);
    if (trim_matrix(numbers, " "))
        return (free_matrex(*numbers), 1);
    if (check_number_color(*numbers))
        return (free_matrex(*numbers), 1);
    return  (0);
}
