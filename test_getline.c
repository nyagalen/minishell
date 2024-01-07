/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_getline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:16:26 by svydrina          #+#    #+#             */
/*   Updated: 2024/01/07 01:28:58 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}	

static void	exec_cmd(char **cmd)
{
	pid_t pid = 0;
	int	status = 0;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		execve(cmd[0], cmd, NULL);
		write_error(cmd[0]);
		exit(EXIT_FAILURE);
	}
}

// // int	truc(char ***cmds)
// {
// 	return();
// }

int	main(int ac, char **av, char **envp)
{
	char	*buffer;
	char	**cmd;
	t_env	*env;

	(void)ac;
	(void)av;
	env = NULL;
	buffer = readline("$>");
	env = init_env(envp);
	while (buffer)
	{
		if (*buffer)
			add_history(buffer);
		cmd = ft_split(buffer, " \n\t");
		if (!buffer[0] || !cmd[0])
		{
			free_arr(cmd);
			buffer = readline("$>");
			continue ;
		}
		if (!ft_strcmp(cmd[0], "exit"))
		{
			free(buffer);
			free_arr(cmd);
			rl_clear_history();
			printf("exit\n");
			exit(0);
		}
		else if (is_built_in(cmd[0]))
			exec_builtin(cmd, env);
		else
		{
			get_absolute_path(cmd);
			exec_cmd(cmd);
		}
		free(buffer);
		free_arr(cmd);
		buffer = readline("$>");
	}
	printf("Bye : |%s|\n", buffer);
	free(buffer);
	free_env(&env);
	rl_clear_history();
}
