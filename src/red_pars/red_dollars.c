/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_dollars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:54:49 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/22 15:54:54 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	red_special_dollars(t_all *a, int x, int y, int mode)
{
	int		len;
	char	*spe;

	spe = ft_itoa(a->info.code);
	len = ft_strlen(spe);
	if (mode == 2)
		ft_strlcpy(&a->info.new_r[y], spe, len + 1);
	if (mode == 1)
		a->info.red_l = a->info.red_l + len;
	free(spe);
	if (mode == 2)
		return (len - 1);
	return (x + 1);
}

int	red_skip_dollars2(t_all *a, char *buf, int x, int m)
{
	char	c;

	c = buf[x + 1];
	if (x + 1 < a->info.b_len && buf[x + 1])
	{
		if ((m == 1 || m == 3) && c == '?')
			return (-3);
		if (m == 1 && (c == 34 || c == 39))
			return (-2);
		if (m == 2 && (c == 34 || c == 39))
			return (x + 1);
	}
	return (skip_char(&buf[x + 1], '_', 2));
}
/*retourne la taille du dollars*/

int	red_skip_dollars(t_all *a, char *buf, int x, int m)
{
	char	*tmp_env;
	int		y;

	tmp_env = NULL;
	y = red_skip_dollars2(a, buf, x, m);
	if (y == -2)
		return (1);
	if (y == -3)
		return (red_special_dollars(a, x, 0, 1));
	tmp_env = malloc(sizeof(char) * (++y));
	if (!tmp_env)
		return (a->info.error = 1, -2);
	ft_strlcpy(tmp_env, &buf[x + 1], y);
	if (find_variable(tmp_env, a->env) == 1)
	{
		m = ft_strlen(find_var_val(tmp_env, a->env));
		a->info.red_l = a->info.red_l + m - 1;
		return (y - 1);
	}
	free(tmp_env);
	if (y > 1)
		return (y);
	++a->info.red_l;
	a->info.q = 1;
	return (1);
}

int	red_add_dollars(t_all *a, int x, int y, int m)
{
	char	*tmp_env;
	int		len;

	tmp_env = NULL;
	len = skip_dollars2(a, x, m);
	if (len == -2)
		return (-1);
	if (len == -3)
		return (red_special_dollars(a, x, y, 2));
	tmp_env = malloc(sizeof(char) * (len + 1));
	if (!tmp_env)
		return (a->info.error = 1, -2);
	ft_strlcpy(tmp_env, &a->info.buf[x + 1], len + 1);
	if (find_variable(tmp_env, a->env) == 1)
	{
		m = a->info.red_l;
		len = red_var_copy(&a->info.new_r[y], find_var_val(tmp_env, a->env), m);
	}
	else if (len == 0 && ++len >= 0)
		a->info.new_r[y] = '$';
	else
		len = 0;
	free(tmp_env);
	return (len - 1);
}
