/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:23:58 by svydrina          #+#    #+#             */
/*   Updated: 2023/12/02 15:36:19 by svydrina         ###   ########.fr       */
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

void	free_arr(char **arr);
void	get_absolute_path(char **cmd);
void	write_error(char *cmd);
int		is_built_in(char *cmd);
void	built_in_cd(char *path);
void	built_in_pwd(void);
void	exec_builtin(char **cmd);
void	write_cd_error(char *file);

#endif
