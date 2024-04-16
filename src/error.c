/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:29:49 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/14 06:15:26 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	failed_exec(char *exec, t_env *env)
{
	int	code;
	DIR	*folder;
	int	fd;

	fd = open(exec, O_WRONLY);
	folder = opendir(exec);
	code = 0;
	if (value_by_name("PATH", env) && !ft_strchr(exec, '/'))
		code = write_error(exec);
	else if ((!value_by_name("PATH", env) && !ft_strchr(exec, '/'))
		|| (access(exec, F_OK) && fd == -1 && folder == NULL))
		code = no_such_file_error(exec);
	else if (fd == -1 && folder != NULL)
		code = is_a_dir_err(exec);
	else if (folder == NULL && access(exec, X_OK))
		code = perm_denied(exec);
	if (folder)
		closedir(folder);
	if (fd > 0)
		close(fd);
	return (code);
}

int	write_error(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		write(2, &cmd[i], 1);
		i++;
	}
	write(2, ": command not found\n", 20);
	return (127);
}

int	write_cd_error(char *file)
{
	int	i;

	i = -1;
	write(2, "minishell: cd: ", 15);
	while (file[++i])
		write(2, &file[i], 1);
	write(2, ": No such file or directory\n", 28);
	return (1);
}

int	no_such_file_error(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (127);
}

int	write_pipe_error(void)
{
	write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	return (2);
}
