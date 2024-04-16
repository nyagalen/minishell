/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:02:34 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/16 20:02:37 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	two_pipe_err(t_infos *i, int x, int m)
{
	if (m == 1 && !i->buf[x])
		return (i->error = 6, -2);
	if (m == 2 && !i->buf[x])
		return (i->error = 5, -2);
	if (i->buf[x] && i->buf[x] == '|')
	{
		if (i->buf[x + 1] && i->buf[x + 1] == '|')
			return (i->error = 4, -2);
		return (i->error = 3, -2);
	}
	return (0);
}

int	rev_red_err2(t_infos *i, int x)
{
	if (i->buf[x] && i->buf[x] == '|')
		return (i->error = 8, -2);
	if (i->buf[x] && i->buf[x] == '>')
		return (i->error = 9, -2);
	return (i->error = 7, -2);
}

int	rev_red_err1(t_infos *i, int x, int m)
{
	int	y;

	if ((m == 1 || m == 2) && !i->buf[x])
		return (i->error = 6, -2);
	if (m == 4 && (!i->buf[x] || i->buf[x] != '>'))
		return (i->error = 11, -2);
	if (m == 5)
		return (i->error = 10, -2);
	if (m == 6 || (m == 4 && i->buf[x] == '>'))
		return (i->error = 12, -2);
	if (i->buf[x] == '>' && (m == 2 || m == 1))
	{
		if (m == 1 && two_pipe_err(i, skip_space(i->buf, x + 1, 1), 1) == -2)
			return (-2);
	}
	y = skip_space(i->buf, x + 1, 1);
	if (i->buf[y] == '>' && rev_red_err2(i, y + 1) == -2)
		return (-2);
	return (0);
}
/* 
if 1: <\0 | <<\0 | <<<\0
if 2: <<<<\0
if 3: <<<<<\0
if 4: <<<<<<\0 || <<<<>?
if 5: <>?

	if 6: <>\0 | <>| | <>|| | <>> 
	if 7: <<>> | <<<>> 
*/

int	redxpipe_err(t_infos *i, int x, int y, int m)
{
	y = skip_space(i->buf, x, 1);
	if (two_pipe_err(i, y, 1) == -2)
		return (-2);
	if (m > 0 && i->buf[y] && i->buf[y] == '>')
	{
		if (i->buf[y + 1] && i->buf[y + 1] == '|')
			return (i->error = 8, -2);
		if (i->buf[y + 1] && i->buf[y + 1] == '>')
			return (i->error = 9, -2);
		if (m != 2 || (i->buf[x] && i->buf[x] != '>'))
			return (i->error = 7, -2);
	}
	if (i->buf[y] && i->buf[y] == '<')
	{
		if (i->buf[y + 1] && i->buf[y + 1] == '<')
		{
			if (i->buf[y + 2] && i->buf[y + 2] == '<')
				return (i->error = 13, -2);
			return (i->error = 10, -2);
		}
		return (i->error = 11, -2);
	}
	return (0);
}

int	check_begin2(t_infos *i, int x, int y)
{
	if (i->buf[x] && i->buf[x] == '>')
	{
		if (i->buf[x + 1] && i->buf[x + 1] == '|')
			i->buf[x + 1] = ' ';
		if (i->buf[x + 1] && i->buf[x + 1] == '>'
			&& redxpipe_err(i, x + 2, 0, 1) == -2)
			return (-2);
		if (i->buf[x + 1] && i->buf[x + 1] == '|')
		{
			if (redxpipe_err(i, x + 2, y, 1) == -2)
				return (-2);
		}
		if (redxpipe_err(i, x + 1, y, 2) == -2)
			return (-2);
	}
	return (0);
}
