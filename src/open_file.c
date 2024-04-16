/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:26:41 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/15 18:21:07 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	check_error(char *filename, int *fdout)
{
	DIR	*folder;

	folder = opendir(filename);
	if (access(filename, F_OK))
		return (no_such_file_error(filename));
	else if (*fdout == -1 && folder != NULL)
	{
		closedir(folder);
		return (is_a_dir_err(filename));
	}
	else if (*fdout == -1 && folder == NULL)
		return (perm_denied(filename));
	if (folder)
		closedir(folder);
	return (0);
}

int	open_out(char *red, int *fdout, char mode)
{
	char	*filename;
	int		code;

	code = 0;
	filename = NULL;
	if (mode == 'a')
		filename = red + 2;
	else if (mode == 't')
		filename = red + 1;
	if (*filename == 0)
		return (no_such_file_error(filename) > 0);
	if (mode == 'a')
		*fdout = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (mode == 't')
		*fdout = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	code = check_error(filename, fdout);
	return (code > 0);
}

static int	is_last_redir(t_all *all, int n, char chevron)
{
	while (all->info.red_tab[n] && all->info.red_tab[n][0] != '|')
	{
		if (chevron == '>' && all->info.red_tab[n][0] == '>')
			return (0);
		else if (chevron == '<' && all->info.red_tab[n][0] == '<')
			return (0);
		n++;
	}
	return (1);
}

static void	assign_inout_or_close(t_all *all, int fdout, int fdin, int n)
{
	if (!all->info.red_tab[n + 1]
		|| (all->info.red_tab[n + 1][0] && all->info.red_tab[n + 1][0] == '|'))
	{
		all->info.instr.out = fdout;
		all->info.instr.in = fdin;
	}
	else
	{
		if (all->info.red_tab[n][0] == '>' && !is_last_redir(all, n + 1, '>'))
			ft_close(fdout);
		else if (all->info.red_tab[n][0] == '>'
			&& is_last_redir(all, n + 1, '>'))
			all->info.instr.out = fdout;
		if (all->info.red_tab[n][0] == '<' && !is_last_redir(all, n + 1, '<'))
			ft_close(fdin);
		else if (all->info.red_tab[n][0] == '<'
			&& is_last_redir(all, n + 1, '<'))
			all->info.instr.in = fdin;
	}
}

int	get_inf_outf(t_all *all)
{
	int	n;
	int	fdin;
	int	fdout;
	int	handle_err;

	n = all->info.instr.red_start;
	fdin = all->info.instr.in;
	fdout = all->info.instr.out;
	while (all->info.red_tab[n] && all->info.red_tab[n][0] != '|')
	{
		handle_err = handle_err_set_index(all, &fdin, &fdout, n);
		if (handle_err == -1)
			return (-1);
		if (handle_err)
			return (0);
		assign_inout_or_close(all, fdout, fdin, n);
		n++;
	}
	all->info.instr.red_start = n + (all->info.red_tab[n]
			&& all->info.red_tab[n][0] == '|');
	return (n + (all->info.red_tab[n] && all->info.red_tab[n][0] == '|'));
}
