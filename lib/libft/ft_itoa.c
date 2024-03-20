/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:03:06 by svydrina          #+#    #+#             */
/*   Updated: 2023/05/13 20:49:42 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	int		len;
	long	l;

	len = 0;
	l = n;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		l *= -1;
	}
	while (l > 0)
	{
		len++;
		l /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*num_str;
	int		i;

	i = count_len(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	num_str = malloc(i + 1);
	num_str[i--] = '\0';
	if (!num_str)
		return (NULL);
	if (n < 0 && n > -2147483648)
	{
		num_str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		num_str[i--] = n % 10 + 48;
		n /= 10;
	}
	return (num_str);
}
