/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:23:57 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/03 23:26:19 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	sig_heredoc(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
}

int	is_delim(char *input, char *eof)
{
	return (ft_strlen(input) == ft_strlen(eof)
		&& !strncmp(input, eof, ft_strlen(eof)));
}

static void	heredoc_child(t_all *all, int *fdin, char *eof)
{
	char	*input;

	input = NULL;
	signal(SIGQUIT, sig_heredoc);
	signal(SIGINT, SIG_DFL);
	input = readline("> ");
	*fdin = open(".txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fdin == -1)
		perror("file won't open");
	while (input && !is_delim(input, eof))
	{
		ft_putendl_fd(input, *fdin);
		free(input);
		input = NULL;
		input = readline("> ");
	}
	end_heredoc(input, all->info.instr.line, eof);
	free_resources_child(&all->info, all->env);
	ft_close(*fdin);
	exit (0);
}

int	heredoc(t_all *all, char *red, int *fdin)
{
	char	*eof;
	int		pid;
	int		sig;
	int		status;

	eof = red + 2;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
		heredoc_child(all, fdin, eof);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		printf("\n");
		return (128 + sig);
	}
	*fdin = open(".txt", O_RDONLY, 0644);
	unlink(".txt");
	return (0);
}

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 130;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
}
