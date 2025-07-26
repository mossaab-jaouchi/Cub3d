/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:09:10 by achamdao          #+#    #+#             */
/*   Updated: 2024/11/07 11:58:58 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	c1;
	int		i;

	i = 0;
	c1 = (char)c;
	while (str[i])
		i++;
	if (c1 == '\0')
		return ((char *)str + i);
	while (i)
	{
		if (str[i] == c1)
			return ((char *)str + i);
		i--;
	}
	if (str[i] == c1)
		return ((char *)str);
	return (NULL);
}
