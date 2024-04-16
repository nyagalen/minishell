/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:23:57 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/15 23:23:39 by svydrina         ###   ########.fr       */
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
	else if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		g_sig = 130;
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_heredoc);
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
	ft_close(*fdin);
}

int	heredoc(t_all *all, char *red, int *fdin)
{
	char	*eof;
	int		hold_fd;

	eof = red + 2;
	hold_fd = dup(STDIN_FILENO);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	heredoc_child(all, fdin, eof);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	ft_close(*fdin);
	if (!g_sig)
		*fdin = open(".txt", O_RDONLY, 0644);
	unlink(".txt");
	dup2(hold_fd, STDIN_FILENO);
	close(hold_fd);
	return (g_sig);
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
