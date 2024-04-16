/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:17:39 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/12 21:17:41 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	cutting_buf(t_infos *i, int save)
{
	++save;
	if (!i->buf[++save])
		return (save);
	if (i->buf[save] == '|' && i->buf[save + 1] == '|')
		return (i->error = 4, -2);
	else if (i->buf[save] == '|')
		return (i->error = 3, -2);
	save = skip_space(i->buf, save, 1);
	if (two_pipe_err(i, save, 2) == -2)
		return (-2);
	while (save < i->b_len && i->buf[save])
	{
		save = skip_space(i->buf, save, 1);
		if (i->buf[save] && i->buf[save] == '|')
		{
			if (two_pipe_err(i, ++save, 2) == -2)
				return (-2);
			save = skip_space(i->buf, save, 1);
			if (two_pipe_err(i, save, 2) == -2)
				return (-2);
		}
		save++;
	}
	return (save);
}

int	check_pipes(t_infos *i, int save)
{
	int	y;

	y = save;
	if (!i->buf[save + 1])
		return (i->error = 5, save);
	if (i->buf[save + 1] == '|')
	{
		if (cutting_buf(i, save) == -2)
			return (save);
		i->buf[save] = ' ';
		ft_memset(&i->buf[save + 1], 0, i->b_len - save);
		i->b_len = save + 1;
		return (save + 1);
	}
	y++;
	y = skip_space(i->buf, y, 1);
	if (two_pipe_err(i, y, 2) == -2)
		return (save);
	i->n_pipe++;
	i->p_check = 1;
	i->tab_nbr++;
	return (save + 1);
}

int	check_red2(t_infos *i, int save)
{
	int	y;

	y = save + 1;
	if (i->buf[save] == '>')
	{
		y = skip_space(i->buf, y, 1);
		if (two_pipe_err(i, y, 1) == -2)
			return (-2);
		if (i->buf[y] == '>')
		{
			if (i->buf[y + 1] && i->buf[y + 1] == '>')
				return (i->error = 9, -2);
			if (i->buf[y + 1] && i->buf[y + 1] == '|')
				return (i->error = 8, -2);
			return (i->error = 7, -2);
		}
	}
	return (0);
}

int	check_red(t_infos *i, int save)
{
	int	y;

	y = save;
	if (check_begin2(i, y, 0) == -2)
		return (save);
	if (check_begin3(i, y, 0) == -2)
		return (save);
	if (!i->buf[save + 1])
		return (i->error = 6, save);
	if (i->buf[save] == '>' && i->buf[save + 1] == '|')
	{
		if (!i->buf[save + 2])
			return (i->error = 6, save);
		if (i->buf[save + 2] == '|')
			return (i->error = 4, save);
		i->buf[save + 1] = ' ';
	}
	y++;
	y = skip_space(i->buf, y, 1);
	if (two_pipe_err(i, y, 1) == -2 || check_red2(i, y) == -2)
		return (save);
	i->red_n++;
	return (save + 1);
}

int	check_middle(t_infos *i, int save)
{
	int	y;

	y = save;
	if (i->buf[y])
		i->arg_nbr++;
	if (i->buf[y] == '|')
		return (check_pipes(i, y));
	if (i->p_check == 1 && --i->p_check == 0)
		i->tab_nbr++;
	while (y < i->b_len && (i->buf[y] != ' ' && i->buf[y] != '	'))
	{
		if (i->buf[y] == 34 || i->buf[y] == 39)
		{
			y = y + skip_char(&i->buf[y + 1], i->buf[y], 1) + 2;
			if (y > i->b_len)
				return (i->error = 2, y - 1);
		}
		else if (i->buf[y] == '|' && i->arg_nbr++ >= 0)
			return (check_pipes(i, y));
		else if ((i->buf[y] == '>' || i->buf[y] == '<') && i->arg_nbr++ >= 0)
			return (check_red(i, y));
		else
			y++;
	}
	return (y);
}
/*0"2" 4|'' fdsf | dsf*/
