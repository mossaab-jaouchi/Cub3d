/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:37:52 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:06:42 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static short	free_all(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (-1);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (-1);
}

int	is_sep(char *sep, char char_str)
{
    int i;

    i = 0;
    while (sep[i])
    {
        if (sep[i] == char_str)
            return (1);
        i++;
    }
	return (0);
}

int	count_word(char *str, char *sep)
{
	int	i;
	int	length;
	int	count;

	if (!str)
		return (-2);
	i = 0;
	length = 0;
	count = 0;
	while (str[i])
	{
		if (is_sep(sep, str[i]))
		{
			if (length != 0)
				count++;
			length = 0;
		}
		else
			length++;
		i++;
	}
	if (length != 0)
		count++;
	return (count);
}

static int	copie_word(char *str, char *sep, char **split_arr, int *length)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	if (!str || !split_arr)
		return (-1);
	while (str[++i])
	{
		if (is_sep(sep, str[i]))
		{
			if (*length != 0)
			{
				split_arr[count] = (char *)malloc(*length + 1);
				if (!split_arr[count])
					return (free_all(split_arr));
				ft_strlcpy(split_arr[count++],
					&str[i - (*length)], *length + 1);
			}
			*length = 0;
		}
		else
			(*length)++;
	}
	return (i);
}

char	**new_split(char const *s, char *c)
{
	int		count;
	char	**split_complie;
	int		length;
	int		i;
	char	*str;

	str = (char *)s;
	split_complie = NULL;
	count = count_word(str, c);
	split_complie = (char **)malloc(sizeof(char *) * (count + 1));
	length = 0;
	i = copie_word(str, c, split_complie, &length);
	if (!split_complie || !str || i == -1)
		return (NULL);
	if (length != 0)
	{
		split_complie[count - 1] = (char *)malloc(length + 1);
		if (!split_complie[count - 1])
			free_all(split_complie);
		if (!split_complie[count - 1])
			return (NULL);
		ft_strlcpy(split_complie[count - 1], &str[i - length], length + 1);
	}
	split_complie[count] = NULL;
	return (split_complie);
}
