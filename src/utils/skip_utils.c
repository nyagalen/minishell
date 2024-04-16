/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:13:31 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/08 20:13:33 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	ft_c_count(char c, char *str, int mode)
{
	int	x;
	int	count;

	count = 0;
	x = -1;
	while (str && str[++x])
	{
		if (str[x] == c && mode == 1)
			++count;
		else if (str[x] == c && mode == 2)
			return (x);
	}
	if (mode == 2)
		return (x);
	return (count);
}

int	skip_space(char *str, int x, int m)
{
	while (m == 1 && str && str[x] && (str[x] == ' ' || str[x] == '	'))
		++x;
	while (m == 2 && str && str[x] && str[x] != ' ' && str[x] != '	')
		++x;
	return (x);
}
/*skip les espace en mode 1, skip ce qu'il y a entre les espace en mode 2*/

int	skip_char(char *str, char skip, int m)
{
	int	x;

	x = 0;
	if (!str)
		return (0);
	while (m == 1 && str[x] && str[x] != skip)
		++x;
	while (m == 2 && str[x] && (str[x] == skip || ft_isalnum(str[x]) == 1))
		++x;
	while (m == 3 && str[x] && (str[x] != skip && str[x] != 39))
		++x;
	while (m == 4 && str[x] && (str[x] != skip && str[x] != 34))
		++x;
	return (x);
}
