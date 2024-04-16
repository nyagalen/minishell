/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pars3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:03:03 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/11 10:03:08 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	new_quote(t_all *a, t_infos *i, int x, int save)
{
	if (i->buf[save] == 34)
	{
		while (++save < x && i->buf[save] != 34)
		{
			if (i->buf[save] == '$')
				save = add_dollars2(a, i, save);
			else if (i->buf[save] != 34)
				i->tmp[i->na - 1][++i->w] = i->buf[save];
		}
	}
	else if (i->buf[save] == 39)
	{
		while (++save < x && i->buf[save] != 39)
			i->tmp[i->na - 1][++i->w] = i->buf[save];
	}
	return (save);
}

int	new_argument2(t_all *a, t_infos *i, int save)
{
	if (i->buf[save] == '$' && i->buf[save + 1])
	{
		if (i->buf[save + 1] == 34 || i->buf[save + 1] == 39)
			return (save);
	}
	if (i->buf[save] == '$')
		save = add_dollars2(a, i, save);
	else if (i->buf[save] != '\0')
		i->tmp[i->na - 1][++i->w] = i->buf[save];
	if (i->buf[save] == 34 || i->buf[save] == 39)
		return (--save);
	return (save);
}

int	new_argument(t_all *a, t_infos *i, int x, int save)
{
	i->w = -1;
	i->tmp[i->na - 1] = malloc(sizeof(char) * i->l_arg[i->na - 1]);
	if (!i->tmp[i->na - 1])
		return (i->error = 1, -2);
	while (save < x && i->buf[save] && i->error <= 0)
	{
		if (i->buf[save] == 34 || i->buf[save] == 39)
			save = new_quote(a, i, x, save);
		else if (i->buf[save] != 34 && i->buf[save] != 39)
			save = new_argument2(a, i, save);
		++save;
	}
	if (i->error > 0)
		return (-2);
	i->tmp[i->na - 1][i->l_arg[i->na - 1] - 1] = '\0';
	return (0);
}

int	skip_arg3bis(t_all *a, char *buf, int x)
{
	if (buf[x] == '|')
		return (++x);
	while (x < a->info.b_len && buf[x] != ' ' && buf[x] != '	')
	{
		if (buf[x] == '$')
			x = x + skip_dollars2(a, x, 2);
		if (buf[x] == 34)
			x = count_dollars(a, ++x, 2);
		if (buf[x] == 39 && ++x <= a->info.b_len)
			x = x + skip_char(&buf[x], 39, 1);
		if (buf[x] == '|')
			return (x);
		++x;
	}
	return (x);
}

int	skip_arg3(t_all *a, t_infos *i, int x)
{
	int	save;

	save = -1;
	if (x >= a->info.b_len)
		return (x);
	a->info.na = a->info.na + 1;
	save = x;
	x = skip_arg3bis(a, a->info.buf, x);
	if (save != -1 && new_argument(a, i, x, save) == -2)
		return (-2);
	return (x);
}

/*int skip_arg2test()*/
