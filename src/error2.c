/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 23:17:18 by svydrina          #+#    #+#             */
/*   Updated: 2024/01/30 23:45:06 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	is_a_dir_err(char *exec)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(exec, 2);
	ft_putendl_fd(": Is a directory", 2);
	return (126);
}

int	perm_denied(char *exec)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(exec, 2);
	ft_putendl_fd(": Permission denied", 2);
	return (126);
}
