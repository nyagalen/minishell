/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:33:27 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/22 16:33:31 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	red_var_copy(char *dst, char *model, int l)
{
	int	len;
	int	x;

	len = ft_strlen(model);
	x = -1;
	while (++x < len && x < l && model[x])
		dst[x] = model[x];
	return (x);
}

int	is_pipe(t_all *a, char **s)
{
	s[0] = malloc(sizeof(char) * 2);
	if (!s[0])
		return (a->info.error = 1, -2);
	s[0][0] = '|';
	s[0][1] = '\0';
	return (0);
}

int	is_red(char *s)
{
	if (s[0] == '<' || s[0] == '>')
		return (1);
	return (0);
}

