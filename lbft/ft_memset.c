/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:02:24 by achamdao          #+#    #+#             */
/*   Updated: 2024/11/07 11:08:24 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*k;
	unsigned char	c1;

	k = (unsigned char *)str;
	c1 = (unsigned char)c;
	while (n--)
	{
		*k = c1;
		k++;
	}
	return (str);
}
