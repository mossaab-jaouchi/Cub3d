/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:36:40 by achamdao          #+#    #+#             */
/*   Updated: 2024/11/17 08:31:22 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_int(int nb)
{
	long	num;
	int		i;

	i = 0;
	num = nb;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		i++;
	}
	while (num)
	{
		num = (num / 10);
		i++;
	}
	return (i);
}

static char	*ft_itoa_negative(int n, char *int_char)
{
	long	num;
	int		len;

	len = len_int(n);
	num = n;
	if (num < 0)
	{
		int_char[0] = '-';
		num *= -1;
	}
	while (len > 1)
	{
		int_char[len - 1] = ((num % 10) + '0');
		num = (num / 10);
		len--;
	}
	int_char[len_int(n)] = '\0';
	return ((int_char));
}

char	*ft_itoa(int n)
{
	long	num;
	char	*int_char;
	int		len;

	len = len_int(n);
	num = n;
	int_char = (char *)malloc((len + 1) * 1);
	if (!int_char)
		return (NULL);
	if (num < 0)
		return (ft_itoa_negative(n, int_char));
	while (len)
	{
		int_char[len - 1] = ((num % 10) + '0');
		num = (num / 10);
		len--;
	}
	int_char[len_int(n)] = '\0';
	return ((int_char));
}
