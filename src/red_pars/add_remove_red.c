/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_remove_red.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:17:10 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/21 19:17:14 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	add_red_to_34(t_all *a, int x, int save)
{
	int	quote;
	int	dol;

	quote = x + skip_char(&a->info.buf[x], 34, 1);
	save = skip_char(&a->info.buf[x], '$', 4);
	dol = x + save;
	while (x < quote && a->info.error <= 0)
	{
		ft_strlcpy(&a->info.new_r[a->info.w], &a->info.buf[x], save + 1);
		a->info.w = a->info.w + save;
		x = x + save;
		if (dol < quote)
		{
			a->info.w = a->info.w + red_add_dollars(a, x, a->info.w, 3) + 1;
			save = skip_char(&a->info.buf[x + 1], '_', 2) + 1;
			x = x + save;
			save = skip_char(&a->info.buf[x], '$', 4);
			dol = dol + save;
		}
	}
	a->info.w--;
	return (1);
}

int	add_quotes_doll(t_all *a, int x, int save)
{
	if (a->info.buf[x] == 34 && add_red_to_34(a, ++x, save) > 0)
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
	while (++i->w < i->red_l - i->q && i->buf[x] && i->error <= 0)
	{
		if (i->buf[x] == 34 || i->buf[x] == 39)
			x = add_quotes_doll(a, x, save);
		else if (i->buf[x] == '$')
		{
			a->info.w = a->info.w + red_add_dollars(a, x, a->info.w, 1);
			save = skip_char(&a->info.buf[x + 1], '_', 2) + 1;
			if (a->info.buf[x + 1] == '?')
				save = 1;
			x = x + save;
		}
		else if (is_red(&i->buf[x]) == 1 || i->buf[x] == '|')
			break ;
		else
			i->new_r[i->w] = i->buf[x++];
	}
	if (i->error > 0)
		return (-2);
	return (0);
}

char	*add_red2(t_all *a, int x)
{
	int		save;

	a->info.w = -1;
	save = x;
	a->info.new_r = malloc(sizeof(char) * (a->info.red_l + 1));
	if (!a->info.new_r)
		return (a->info.error = 1, NULL);
	while (a->info.buf[save] == a->info.buf[x])
		a->info.new_r[++a->info.w] = a->info.buf[x++];
	if (a->info.q > 0)
		a->info.new_r[++a->info.w] = 39;
	x = skip_space(a->info.buf, x, 1);
	printf("r: |%s| ; &new_r[a->info.w: %d]: |%s|\n", a->info.new_r, a->info.w, &a->info.new_r[a->info.w]);
	if (add_red3(a, &a->info, x, save) == -2 || a->info.error > 0)
		return (NULL);
	printf("r: |%s| ; &new_r[a->info.w: %d]: |%s|\n", a->info.new_r, a->info.w, &a->info.new_r[a->info.w]);
	if (a->info.q > 0)
		a->info.new_r[a->info.red_l - 1] = 39;
	a->info.new_r[a->info.red_l] = '\0';
	return (a->info.new_r);
}

//$>ls >fdsf >$USER <l | >$U <$II' ' fadsofn

int	remove_red(t_infos *i, int x, int save)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (i->b_len - save + 1));
	if (!tmp)
		return (i->error = 1, -2);
	ft_strlcpy(tmp, i->buf, x + 1);
	ft_strlcpy(&tmp[x], &i->buf[x + save], i->b_len - x - save + 1);
	tmp[i->b_len - save + 1] = '\0';
	i->b_len = ft_strlen(tmp);
	free(i->buf);
	i->buf = tmp;
	return (0);
}
