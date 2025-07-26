/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_two_parts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:22:06 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:07:14 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int skip_separators(char *str, char *sep)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!is_sep(sep, str[i]))
            break ;
        i++;
    }
    return (i);
}

int get_end_word(char *str, char *sep)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (is_sep(sep, str[i]))
            break ;
        i++;
    }
    return (i);
}

char    **allocate_matrix(int number)
{
    if (number >= 2)
        return (malloc(3 * sizeof(char *)));
    else if (number > 0)
        return (malloc(2 * sizeof(char *)));
    return (NULL);
}

int	stored_matrix(char **matrix, char *str, char *sep, int number_word)
{
	int	start;
	int	length_first;
	int	end;
	int	length;

	length = ft_strlen(str);
	if (number_word >= 2)
		end = 2;
	else
		end = 1;
	length_first = get_end_word(str, sep);
	matrix[0] = ft_strndup(str, length_first);
	if (!matrix[0])
		return (free(matrix), 0);
	start = length_first + skip_separators(&str[length_first], sep);
	if (number_word >= 2)
	{
		matrix[1] = ft_strndup(&str[start], length);
		if (!matrix[1])
			return (free_matrex(matrix), 0);
	}
	matrix[end] = NULL;
	return (1);
}

char	**split_in_two_parts(char *str, char *sep)
{
	char	**matrix;
	int		number_word;

	if (!str || !sep)
		return (NULL);
	number_word = count_word(str, sep);
	matrix = allocate_matrix(number_word);
	if (!matrix)
		return (NULL);
	if (!stored_matrix(matrix, str, sep, number_word))
		return (NULL);
	return (matrix);
}
