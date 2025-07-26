/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parts_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:51:17 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:06:30 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char    is_whitespace(char c)
{
    return (c == ' ' || c == '\n');
}

char check_whitespace(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!is_whitespace(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int get_length_map(char **matrex, short skeep)
{
    int i;
    int count;

    i = 0;
    count = 0;
    if (!matrex)
        return (0);
    while (matrex[i])
    {
        if (!check_whitespace(matrex[i]) && skeep)
            skeep--;
        if (!skeep)
            count++;
        i++;
    }
    return (count);
}

char    get_clean_map(char **matrex, char **clean_matrex, short skeep, int size)
{
    int i;
    int count;
    int skeep_matrex;

    i = 0;
    count = 0;
    skeep_matrex = skeep;
    while (matrex[i])
    {
        if (!check_whitespace(matrex[i]) && skeep)
            skeep--;
        if (!skeep)
        {
            clean_matrex[count] = ft_strdup(matrex[i]);
            if (!clean_matrex[count])
                return(free_matrex(clean_matrex), -1);
            count++;
        }
        i++;
    }
    clean_matrex[size] = NULL;
    if (count != size)
        return (1);
    return (0);
}

char get_path_color(char **matrex, char **clean_matrex, short skeep, int size)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (matrex[i])
    {
        if (!check_whitespace(matrex[i]) && skeep)
            skeep--;
        if (!skeep)
        {
            if (!check_whitespace(matrex[i]) && count < size)
            {
                clean_matrex[count] = ft_strdup(matrex[i]);
                if (!clean_matrex[count])
                    return(free_matrex(clean_matrex), -1);
                count++;
            }
        }
        i++;
    }
    clean_matrex[size] = NULL;
    if (count != size)
        return (1);
    return (0);
}
