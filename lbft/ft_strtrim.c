/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:09:44 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/26 16:22:19 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set, char flag_free)
{
	int		end;
	int		star;
	char	*trimmed;
	int		i;

	if (!s1)
		return (NULL);
	if (!set)
		return (s1);
	i = 0;
	end = ft_strlen(s1);
	star = 0;
	while (s1[star] && (is_in_set(s1[star], set)))
		star++;
	while (star < end && (is_in_set(s1[end - 1], set)))
		end--;
	trimmed = (char *)malloc((end - star + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	while (star < end)
		trimmed[i++] = s1[star++];
	trimmed[i] = '\0';
	if (flag_free)
		free(s1);
	return (trimmed);
}
