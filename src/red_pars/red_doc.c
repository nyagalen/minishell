/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:41:38 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/13 14:41:43 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	doc_quotes(t_infos *i, char *buf, int x)
{
	int	len;

	len = skip_char(&buf[x], buf[x - 1], 1);
	i->red_l = i->red_l + len;
	return (len + x + 1);
}

int	doc_len(t_infos *i, char *buf)
{
	int	x;
	int	save;

	x = -1;
	save = 0;
	while (buf[0] == buf[++x])
		++i->red_l;
	x = skip_space(buf, x, 1);
	while (x < i->b_len && buf[x] && (buf[x] != ' ' && buf[x] != '	'))
	{
		if (buf[x] == 34 || buf[x] == 39)
			x = doc_quotes(i, buf, ++x);
		else if (buf[x] == '<' || buf[x] == '>' || buf[x] == '|')
			break ;
		else if (++i->red_l > 0)
			++x;
		if (i->error > 0)
			break ;
	}
	return (x);
}

int	add_doc3(t_infos *i, int x, int save)
{
	while (++i->w < i->red_l && i->buf[x] && i->error <= 0)
	{
		if (i->buf[x] == 34 || i->buf[x] == 39)
		{
			save = skip_char(&i->buf[x + 1], i->buf[x], 1);
			ft_strlcpy(&i->new_r[i->w], &i->buf[++x], save + 1);
			i->w = i->w + save - 1;
			x = x + save + 1;
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

char	*add_doc2(t_infos *i, int x)
{
	int		save;
	int		save2;

	i->w = -1;
	save = x;
	save2 = 0;
	i->new_r = malloc(sizeof(char) * (i->red_l + 1));
	if (!i->new_r)
		return (i->error = 1, NULL);
	if (i->er > 0)
		i->new_r[++i->w] = '1';
	while (i->buf[save] == i->buf[x])
		i->new_r[++i->w] = i->buf[x++];
	x = skip_space(i->buf, x, 1);
	if (add_doc3(i, x, save) == -2 || i->error > 0)
		return (NULL);
	i->new_r[i->red_l] = '\0';
	return (i->new_r);
}

int	add_doc(t_infos *i, int x, int n)
{
	int	save;

	i->red_l = 0;
	i->er = 0;
	i->new_r = NULL;
	save = doc_len(i, &i->buf[x]);
	if (i->error > 0)
		return (-2);
	add_doc2(i, x);
	i->red_tab[n] = i->new_r;
	if (i->error > 0)
		return (-2);
	if (!i->red_tab[n] || remove_red(i, x, save) == -2)
		return (i->error = 1, -2);
	return (0);
}
