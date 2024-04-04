/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:26:41 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/04 19:56:43 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	open_out(char *red, int *fdout, char mode)
{
	DIR		*folder;
	char	*filename;
	int		code;

	code = 0;
	if (mode == 'a')
	{
		filename = red + 2;
		*fdout = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else if (mode == 't')
	{
		filename = red + 1;
		*fdout = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	folder = opendir(filename);
	if (*fdout == -1 && folder != NULL)
		code = is_a_dir_err(filename);
	if (*fdout == -1 && folder == NULL)
		code = perm_denied(filename);
	if (folder)
		closedir(folder);
	return (code > 0);
}

int	open_in(char *red, int *fdin)
{
	if (access(red + 1, F_OK) == -1)
		return (no_such_file_error(red + 1) > 0);
	*fdin = open(red + 1, O_RDONLY);
	if (*fdin == -1 && access(red + 1, R_OK) == -1)
		return (perm_denied(red + 1) > 0);
	return (0);
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
		ft_close(fdout);
		ft_close(fdin);
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
		if (handle_err)
			return (0);
		assign_inout_or_close(all, fdout, fdin, n);
		n++;
	}
	all->info.instr.red_start = n + (all->info.red_tab[n]
			&& all->info.red_tab[n][0] == '|');
	return (n + (all->info.red_tab[n] && all->info.red_tab[n][0] == '|'));
}
