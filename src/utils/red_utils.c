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
	if (s[0] == '>')
		return (1);
	if (s[0] == '<' && (!s[1] || s[1] != '<'))
		return (1);
	if (s[0] == '<' && s[1] == '<')
		return (2);
	return (0);
}

int	remove_red(t_infos *i, int x, int save)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (i->b_len - save + 1));
	if (!tmp)
		return (i->error = 1, -2);
	ft_strlcpy(tmp, i->buf, x + 1);
	ft_strlcpy(&tmp[x], &i->buf[x + save], i->b_len - x - save + 1);
	tmp[i->b_len - save] = '\0';
	i->b_len = ft_strlen(tmp);
	free(i->buf);
	i->buf = tmp;
	return (0);
}

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
	x++;
	return (2);
}
