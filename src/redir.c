/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:18:16 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/20 20:21:13 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	out_trunc(char *red)
{
	return (red[0] && red[1] && red[0] == '>' && red[1] != '>');
}

static int	out_app(char *red)
{
	return (!ft_strncmp(red, ">>", 2));
}

static int	infile(char *red)
{
	return (red[0] && red[1] && red[0] == '<' && red[1] != '<');
}

static	int	open_file(char *red, int *fdin, int *fdout)
{
	int	code;

	code = 0;
	if (out_trunc(red))
		code = open_out(red, fdout, 't');
	else if (out_app(red))
		code = open_out(red, fdout, 'a');
	else if (infile(red))
		code = open_in(red, fdin);
	printf("code from open_file: %d\n", code);
	return (code);
}

int	get_inf_outf(t_instr *instr, char **red_tab)
{
	int	i;
	int	fdin;
	int	fdout;

	i = instr->red_start;
	fdin = instr->in;
	fdout = instr->out;
	while (red_tab[i] && red_tab[i][0] != '|')
	{
		if (open_file(red_tab[i], &fdin, &fdout))
			return (0);
		if (!red_tab[i + 1] || red_tab[i + 1][0] == '|')
		{
			instr->out = fdout;
			instr->in = fdin;
		}
		else
		{
			ft_close(fdout);
			ft_close(fdin);
		}
		i++;
	}
	return (i);
}
