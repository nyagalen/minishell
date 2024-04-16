/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:18:16 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/11 20:59:05 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	out_trunc(char *red)
{
	return (red[0] && red[0] == '>' && red[1] != '>');
}

static int	out_app(char *red)
{
	return (!ft_strncmp(red, ">>", 2));
}

static int	infile(char *red)
{
	return (red[0] && red[0] == '<' && red[1] != '<');
}

static char	*name_ind_ambiguous(char *red)
{
	int	i;

	i = 1;
	while (red[i] && (red[i] == '>' || red[i] == '<'))
		i++;
	return (red + i);
}

int	open_file(t_all *all, char *red, int *fdin, int *fdout)
{
	int	code;

	code = 0;
	if (red[0] == '1')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(name_ind_ambiguous(red), 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		return (1);
	}
	if (out_trunc(red))
		code = open_out(red, fdout, 't');
	else if (out_app(red))
		code = open_out(red, fdout, 'a');
	else if (infile(red))
		code = open_in(red, fdin);
	else if (!all->info.n_pipe && is_heredoc(red))
		code = heredoc(all, red, fdin);
	else if (all->info.n_pipe && is_heredoc(red))
		code = open_heredoc_pipes(all, fdin);
	return (code);
}
