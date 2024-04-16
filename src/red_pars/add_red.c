/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_red.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:53:28 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/13 17:53:32 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	add_red_to_34(t_all *a, t_infos *i, int x, int save)
{
	int	quote;
	int	dol;

	quote = x + skip_char(&i->buf[x], 34, 1);
	save = skip_char(&i->buf[x], '$', 4);
	dol = x + save;
	while (x < quote && i->error <= 0)
	{
		ft_strlcpy(&i->new_r[i->w], &i->buf[x], save + 1);
		i->w = i->w + save;
		x = x + save;
		if (dol < quote)
		{
			i->w = i->w + red_add_dollars(a, x, i->w, 3) + 1;
			save = skip_char(&i->buf[x + 1], '_', 2) + 1;
			if (ft_isdigit(i->buf[x + 1]) == 1 || i->buf[x + 1] == '?')
				save = 2;
			x = x + save;
			save = skip_char(&i->buf[x], '$', 4);
			dol = dol + save;
		}
	}
	i->w--;
	return (1);
}

int	add_quotes_doll(t_all *a, int x, int save)
{
	if (a->info.buf[x] == 34 && add_red_to_34(a, &a->info, ++x, save) > 0)
		return (x + skip_char(&a->info.buf[x], 34, 1) + 1);
	else if (a->info.buf[x] == 39)
	{
		save = skip_char(&a->info.buf[x + 1], a->info.buf[x], 1);
		ft_strlcpy(&a->info.new_r[a->info.w], &a->info.buf[++x], save + 1);
		a->info.w = a->info.w + save - 1;
		return (x + save + 1);
	}
	return (0);
}

int	add_red3(t_all *a, t_infos *i, int x, int save)
{
	while (++i->w < i->red_l && i->buf[x] && i->error <= 0)
	{
		if (i->buf[x] == 34 || i->buf[x] == 39)
			x = add_quotes_doll(a, x, save);
		else if (i->buf[x] == '$')
		{
			i->w = i->w + red_add_dollars(a, x, i->w, 1);
			save = skip_char(&i->buf[x + 1], '_', 2) + 1;
			if (i->buf[x + 1] == '?')
				save = 2;
			else if (ft_isdigit(i->buf[x + 1]) == 1)
				save = 2;
			x = x + save;
		}
		else if (is_red(&i->buf[x]) >= 1 || i->buf[x] == '|')
			break ;
		else
			i->new_r[i->w] = i->buf[x++];
	}
	if (i->error > 0)
		return (-2);
	return (0);
}

int	add_first(t_all *a, t_infos *i, int x, int save2)
{
	if (i->buf[x] && i->error <= 0 && i->buf[x] == '$' && i->w < i->red_l)
	{
		save2 = i->w + red_add_first_dollars(a, x, i->w, 1);
		if (save2 > i->w)
		{
			ft_strlcpy(&i->new_r[save2], &i->buf[x], i->red_l - i->w);
			i->new_r[i->red_l] = '\0';
			return (1);
		}
	}
	return (0);
}

char	*add_red2(t_all *a, t_infos *i, int x)
{
	int		save;

	i->w = -1;
	save = x;
	i->new_r = malloc(sizeof(char) * (i->red_l + 1));
	if (!i->new_r)
		return (i->error = 1, NULL);
	if (i->er > 0)
		i->new_r[++i->w] = '1';
	while (i->buf[save] == i->buf[x])
		i->new_r[++i->w] = i->buf[x++];
	x = skip_space(i->buf, x, 1);
	if (add_first(a, i, x, 0) == 1)
		return (i->new_r);
	if (add_red3(a, &a->info, x, save) == -2 || i->error > 0)
		return (NULL);
	i->new_r[i->red_l] = '\0';
	return (i->new_r);
}

//$>ls >fdsf >$USER <l | >$U <$II' ' fadsofn
