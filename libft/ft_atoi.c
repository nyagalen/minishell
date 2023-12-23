/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:49:03 by svydrina          #+#    #+#             */
/*   Updated: 2023/05/10 14:17:17 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_whitespace(char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

int	ft_atoi(const char *nptr)
{
	long	result;
	int		i;
	int		sign;

	result = 0;
	i = 0;
	sign = 1;
	while (nptr[i] && is_whitespace(nptr[i]))
		i++;
	if (nptr[i] && nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] && nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] > 47 && nptr[i] < 58)
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return ((int)result * sign);
}
