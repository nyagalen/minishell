/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_getline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:16:26 by svydrina          #+#    #+#             */
/*   Updated: 2023/12/02 15:03:31 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main()
{
	char	*buffer = NULL;
	size_t	buf_size = 2048;
	char	**cmd;

	buffer = calloc(sizeof(char), buf_size);
	if (buffer == NULL)
	{
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}
	write(1, "$> ", 3);
	while (getline(&buffer, &buf_size, stdin) > 0)
	{
		cmd = ft_split(buffer, " \n\t");
		if (!buffer[0] || !cmd[0])
		{
			free_arr(cmd);
			write(1, "$> ", 3);
			continue ;
		}
		get_absolute_path(cmd);
		if (cmd[0] == NULL)
			printf("command not found cmd null\n");
		else if (!is_built_in(cmd[0]))
		{
			get_absolute_path(cmd);
			exec_cmd(cmd);
		}
		else
			exec_builtin(cmd);
		free_arr(cmd);
		write(1, "$> ", 3);
	}
	printf("Bye \n");
	free(buffer);
}
