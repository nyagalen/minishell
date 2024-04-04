/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:21:35 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/03 23:24:20 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	end_heredoc(char *input, int line, char *eof)
{
	if (!input)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(eof, 2);
		ft_putendl_fd("')", 2);
	}
	else
		free(input);
}

static void	heredoc_child_pipes(t_all *all, char *eof, int hd_i)
{
	char	*input;
	int		fd;

	input = NULL;
	signal(SIGQUIT, sig_heredoc);
	signal(SIGINT, SIG_DFL);
	input = readline("> ");
	fd = open(all->info.hd_files[hd_i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror("file won't open");
	while (input && !is_delim(input, eof))
	{
		ft_putendl_fd(input, fd);
		free(input);
		input = NULL;
		input = readline("> ");
	}
	end_heredoc(input, all->info.instr.line, eof);
	free_resources_child(&all->info, all->env);
	ft_close(fd);
	exit (0);
}

int	hd_pipe_parent(t_all *all, int hd_i, char *eof)
{
	int		pid;
	int		sig;
	int		status;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
		heredoc_child_pipes(all, eof, hd_i);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		printf("\n");
		return (128 + sig);
	}
	return (0);
}

int	open_heredoc_pipes(t_all *all, int *fdin)
{
	int	i;

	i = all->info.instr.hd_i;
	*fdin = open(all->info.hd_files[i], O_RDONLY, 0644);
	if (*fdin == -1)
		perror("can't open file");
	unlink(all->info.hd_files[i]);
	all->info.instr.hd_i += 1;
	return (0);
}
