/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:23:58 by svydrina          #+#    #+#             */
/*   Updated: 2024/01/07 00:59:05 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <limits.h>
# include <linux/limits.h>
# include <signal.h>

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}	t_env;

void	free_arr(char **arr);
void	get_absolute_path(char **cmd);
void	write_error(char *cmd);
int		is_built_in(char *cmd);
void	built_in_cd(char *path);
void	built_in_pwd(void);
void	exec_builtin(char **cmd, t_env *env);
void	write_cd_error(char *file);
t_env	*init_env(char **envp);
void	print_env(t_env *env);
void	free_env(t_env **env);
void	env_addback(t_env **env, t_env *new);
t_env	*env_last(t_env *env);
t_env	*env_new(char *new_l);
void	ft_export(char *var, t_env **env);

#endif
