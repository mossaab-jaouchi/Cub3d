/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:06:07 by achamdao          #+#    #+#             */
/*   Updated: 2025/03/18 17:19:02 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	c1;

	c1 = c;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c1)
			return ((char *)str);
		str++;
	}
	if (c1 == '\0')
		return ((char *)str);
	return (0);
}
