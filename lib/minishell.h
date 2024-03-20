/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:23:58 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/20 23:32:14 by svydrina         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>

extern int	g_sig;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_instr
{
	char	***cmd;
	int		n_pipe;
	int		**fd;
	int		in;
	int		out;
	int		status;
	int		red_start;
}	t_instr;

typedef struct s_infos
{
	char	***cmd;
	char	***tcmd;
	char	**tmp;
	char	**red_tab;
	char	*buf;
	int		*l_arg;//liste de la taille de chaque argument
	int		*l_tab;
	int		b_len;
	int		arg_nbr;
	int		tab_nbr;
	int		red_n; //nbr redirections
	int		n_pipe; //faire un char ** separer pour les pipes qui seront vide ?
	int		nbr2;
	int		w; //alternative a une variable qui doit etre reutilisee
	int		error; //signaler l'arret de cmd_tab car erreur detecté (1 = erreur)
	int		p_check; //si oui ou non il y a eu un argument depuis le debut de la pipe
	int		***type;
	int		code;
	int		**fds;
	int		*pids;
	t_instr	instr;
}	t_infos;

typedef struct s_all
{
	t_env	*env;
	t_infos	info;
	char	*buffer;
}	t_all;

//Partie C***********************************************

//cmd_tab.int **fdsc
char	***cmd_tab(t_all *all, char *buffer);
//fct de creation de ***cmd et de debut du parsing
int		split_parse(t_all *all, char *buffer, t_infos *i);

//cmd_conv.cint		find_variable(char *var, t_env *env);
int		find_variable(char *var, t_env *env);
char	*find_var_val(char *var, t_env *env);
char	*var_value_tmp(t_env *env);
char	*var_copy(t_all *a, char *dst, char *model);

//cmd_pars1.c
int		ft_c_count(char c, char *str, int moinsde);
int		skip_space(char *str, int x, int m);
int		skip_arg1bis(t_infos *i, int x);
int		skip_arg1(t_infos *i, int x);
int		argument_nbr(t_all *a, int mode);

//cmd_pars2.c
int		count_dollars(t_all *a, int x, int *nbr, int mode);
int		skip_dollars(t_all *a, int x, int *nbr);
int 	skip_dollars2(t_all *a, int x, int mode);
int		skip_arg2bis(t_all *a, int x, int *nbr);
int		skip_arg2(t_all *a, int x, int *nbr);
int		skip_arg3(t_all *a, int x, int *nbr);

//cmd_malloc1.c
int		add_dollars2(t_all *a, int save);
int		new_argument(t_all *a, int x, int save, int *nbr);

//utils/cmd_utils.c
char	***free_tab3(char ***cmd);
char	**free_tab(char **tab);
//fct de free de free tab3
int		print_tab(char **tab);
void	print_tabx2(char ***tab, int x);
int		print_intx2(int *tab);
int skip_char(char *str, char skip, int m);


//partie S*****************************************************
//dans test_geft_close(infos->pipin);
	// ft_close(infos->pipout);
	// infos->pipin = -1;
	// infos->pipout = -1;tline.c
char	*new_entry(t_infos *info);
void	if_signaled(t_infos *info, int code);
//nouvelle entree de terminal(free buffer + cmd; readline)
int		execpart(t_infos *infos, t_env *env, int i);
void	free_arr(char **arr);
int		exec_cmd(t_infos *infos, char *exec, t_env *env, int i);

//dans path.c
char	*get_absolute_path(char **cmd, t_env *env);
char	*get_bin(char *cmd, char *path);

//dans error.c
int		write_error(char *cmd);
int		write_cd_error(char *file);
int		write_pipe_error(void);
int		failed_exec(char *exec, t_env *env);
int		no_such_file_error(char *filename);

//dans error2.c
int		is_a_dir_err(char *exec);
int		perm_denied(char *exec);

//dans built_in.c
int		is_built_in(char *cmd);
int		built_in_cd(char *path);
int		built_in_pwd(void);
int		exec_builtin(t_infos *infos, t_env *env, int i);

//dans env.c
t_env	*init_env(char **envp);
void	print_env(t_env *env);
void	free_env(t_env **env);
char	*var_value(t_env *env);
char	*value_by_name(char *name, t_env *env);

//dans env_utils.c
void	env_addback(t_env **env, t_env *new);
t_env	*env_last(t_env *env);
t_env	*env_new(char *new_l);
int		index_str(char *str, char c);
int		valid_env_var(char *var);

//dans env2.c
void	ft_export(char *var, t_env **env);
void	replace_line_env(char *line, t_env *env);
int		line_in_env(char *line, t_env *env);
int		export_mult(char **cmd, t_env **env);
//int		valid_ft_close(infos->pipin);
	// ft_close(infos->pipout);
	// infos->pipin = -1;
	// infos->pipout = -1;env_line(char *line);

//dans unset.c
void	ft_unset(char **cmd, t_env **env);
void	env_remove_if(char *var, t_env **env);
void	valid_and_remove(char *var, t_env **env);
int		var_in_line(char *var, char *line);
int		var_in_env(char *var, t_env *env);

//dans exit.c
int		ft_exit(t_infos *infos, t_env **env, int i);
int		check_ex_args(t_infos *infos, char **ex_cmd);
int		atoi_exitcode(t_infos *infos, char *num);
int		exitcode(int code);

//dans echo.c
void	ft_echo(char **cmd);

//dans utils.c
int		tab_size(char **tab);
void	ft_close(int fd);
void	exit_blabla(t_infos *info, int i);
void	free_close_fds_pids(t_infos *info);
void	reset_in_out(t_infos *info);

//dans shlvl.c
t_env	*env_by_name(char *name, t_env *env);
int		lvl_incr(t_env *env);
void	increment_shlvl(t_env *env);

//dans no_pipe.c
void	no_pipe(t_infos *info, t_env *env);

//dans pipe.c
void	loop(t_infos *info, t_env *env);
void	child(int **fds, int i, int n_pipe);	

//dans pipe2.c
void	parent(int **fds, int i, int n_pipe);

//dans redir.c
int		get_inf_outf(t_instr *instr, char **red_tab);

//dans open_file.c
int		open_out(char *red, int *fdout, char mode);
int		open_in(char *red, int *fdin);

#endif
// dsifhids fuidgsifsdgfugs fgdsu fgsugdf fugsdd
/*
variable error transcription:
1 = malloc error
2 = open quote error
3 = | error
4 = || error
5 = fds | error

*/