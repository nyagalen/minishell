/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:23:58 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/17 21:11:30 by svydrina         ###   ########.fr       */
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
	int		cmd_i;
	int		hd_i;
	int		line;
	int		orig_exitcode;
}	t_instr;

typedef struct s_infos
{
	char	***cmd;
	char	***tcmd;
	char	**tmp;
	char	**red_tab;
	char	*new_r;
	char	*buf;
	int		*l_arg;
	int		*l_tab;
	int		b_len;
	int		arg_nbr;
	int		tab_nbr;
	int		red_n;
	int		red_l;
	int		n_pipe;
	int		nbr2;
	int		na;
	int		w;
	int		error;
	int		p_check;
	int		er;
	int		h;
	int		***type;
	int		code;
	int		**fds;
	int		*pids;
	char	**hd_files;
	t_instr	instr;
}	t_infos;

typedef struct s_all
{
	t_env	*env;
	t_infos	info;
	char	*buffer;
}	t_all;

//Partie C***********************************************

//check
//src/check/check_buf.c
int		check_begin5(t_infos *i, int x, int y);
int		check_begin4(t_infos *i, int x, int y);
int		check_begin3(t_infos *i, int x, int y);
int		check_begin1(t_infos *i, int x);
int		check_buf(t_infos *i);
//src/check/check_buf2.c
int		cutting_buf(t_infos *i, int save);
int		check_pipes(t_infos *i, int save);
int		check_red2(t_infos *i, int save);
int		check_red(t_infos *i, int save);
int		check_middle(t_infos *i, int save);
//src/check/pars_errors.c
int		pars_error(int error);

//cmd_pars
//cmd_pars/cmd_pars1.c
int		wipe_dollars2(t_all *a, char *tmp, int x, int len);
int		wipe_dollars(t_all *a, t_infos *i, int x);
int		skip_arg1bis(t_infos *i, int x);
int		skip_arg1(t_all *a, t_infos *i, int x);
int		tab_info(t_all *a, int x);
//src/cmd_pars/cmd_pars2.c
int		skip_arg2bis(t_all *a, t_infos *i, int x);
int		skip_arg2(t_all *a, t_infos *i, int x);
//src/cmd_pars/cmd_pars3.c
int		skip_arg3(t_all *a, t_infos *i, int x);
int		skip_arg3bis(t_all *a, char *buf, int x);
int		new_argument(t_all *a, t_infos *i, int x, int save);
int		new_argument2(t_all *a, t_infos *i, int save);
int		new_quote(t_all *a, t_infos *i, int x, int save);

//create_tab
//src/create_tab/cmd_tab.c
char	***cmd_tab1(t_all *all, char *buffer);
char	***cmd_tab(t_all *all, char *buffer);
int		part_pars(t_all *a, t_infos *i, char *buffer);
int		split_parse(t_all *all, char *buffer, t_infos *i);
int		argument_nbr(t_all *a, t_infos *i, int mode);
//src/create_tab/cmd_conv.c
int		find_variable(char *var, t_env *env);
char	*find_var_val(char *var, t_env *env);
char	*var_value_tmp(t_env *env);
char	*var_copy(t_all *a, char *dst, char *model);
//src/create_tab/cmd_malloc1.c
int		tab_assign1(t_all *a, char **tab, int bx, int len);
char	***assign_null(t_all *a, char ***tcmd);
char	***tab_assign(t_all *a);

//red_pars
//src/red_pars/add_red.c
int		add_first(t_all *a, t_infos *i, int x, int save2);
char	*add_red2(t_all *a, t_infos *i, int x);
int		add_red3(t_all *a, t_infos *i, int x, int save);
int		add_quotes_doll(t_all *a, int x, int save);
int		add_red_to_34(t_all *a, t_infos *i, int x, int save);
//src/red_pars/cmd_red.c
int		add_red(t_all *a, int x, int n);
int		red_init(t_all *a, t_infos *i, int x, int n);
int		red_len(t_all *a, char *buf);
int		skip_red_to_34(t_all *a, char *buf, int x, int len);
int		skip_quotes(t_all *a, char *buf, int x, int m);
//src/red_pars/red_dollars.c
int		red_skip_dollars2(t_all *a, char *buf, int x, int m);
int		red_skip_first_dollars(t_all *a, char *buf, int x, int m);
int		red_skip_dollars(t_all *a, char *buf, int x, int m);
int		red_add_first_dollars(t_all *a, int x, int y, int m);
int		red_add_dollars(t_all *a, int x, int y, int m);
//src/red_pars/red_doc.c
int		doc_quotes(t_infos *i, char *buf, int x);
int		doc_len(t_infos *i, char *buf);
int		add_doc3(t_infos *i, int x, int save);
char	*add_doc2(t_infos *i, int x);
int		add_doc(t_infos *i, int x, int n);

//utils
//src/utils/check_utils.c
int		two_pipe_err(t_infos *i, int x, int mode);
int		rev_red_err2(t_infos *i, int x);
int		rev_red_err1(t_infos *i, int x, int m);
int		redxpipe_err(t_infos *i, int x, int y, int m);
int		check_begin2(t_infos *i, int x, int y);

//src/utils/cmd_utils.c
char	***free_tab3(char ***cmd);
char	**free_tab(char **tab);
int		pars_error_free(t_infos *i, int m);
//src/utils/dollars_utils.c
int		special_dollars(t_all *a, int x, int nbr, int mode);
int		add_dollars2(t_all *a, t_infos *i, int save);
int		skip_dollars2(t_all *a, int x, int m);
int		skip_dollars(t_all *a, t_infos *i, int x);
int		count_dollars(t_all *a, int x, int mode);
//src/utils/print_utils.c
int		print_tab(char **tab);
void	print_tabx2(char ***tab, int x);
int		print_intx2(int *tab);
//src/utils/red_utils.c
int		red_var_copy(char *dst, char *model, int l);
int		is_pipe(t_all *a, char **s);
int		is_red(char *s);
int		remove_red(t_infos *i, int x, int save);
int		red_special_dollars(t_all *a, int x, int y, int mode);
//src/utils/skip_utils.c
int		ft_c_count(char c, char *str, int moinsde);
int		skip_space(char *str, int x, int m);
int		skip_char(char *str, char skip, int m);

//partie S*****************************************************			
//dans test_geft_close(infos->pipin);
	// ft_close(infos->pipout);
	// infos->pipin = -1;
	// infos->pipout = -1;tline.c
char	*new_entry(t_infos *info);
int		if_signaled(int code);
//nouvelle entree de terminal(free buffer + cmd; readline)
int		execpart(t_infos *infos, t_env *env, int i, t_all *all);
void	free_arr(char **arr);
int		exec_cmd(t_infos *infos, char *exec, t_env *env, int i);

//dans path.c
char	*get_absolute_path(char **cmd, t_env *env);
char	*get_bin(char *cmd, char *path);

//dans error.	reset_in_out(&all.info);c
int		write_error(char *cmd);
int		write_cd_error(char *file);
int		write_pipe_error(void);
int		failed_exec(char *exec, t_env *env);
int		no_such_file_error(char *filename);

//dans error2.c
int		is_a_dir_err(char *exec);
int		perm_denied(char *exec);

//dans built_in.	reset_in_out(&all.info);c
int		is_built_in(char *cmd);
int		built_in_cd(char **cmd, t_env *env, t_all *all);
int		built_in_pwd(void);
int		exec_builtin(t_infos *infos, t_env *env, int i, t_all *all);

//dans env.c
t_env	*init_env(char **envp, t_all *all);
void	print_env(t_env *env);
void	free_env(t_env **env);
char	*var_value(t_env *env);
char	*value_by_name(char *name, t_env *env);

//dans env_utils.c
void	env_addback(t_env **env, t_env *new);
t_env	*env_last(t_env *env);
t_env	*env_new(char *new_l, t_all *all);
int		index_str(char *str, char c);
int		valid_env_var(char *var);

//dans env2.c
int		ft_export(char *var, t_env **env, t_all *all);
int		replace_line_env(char *line, t_env *env);
int		line_in_env(char *line, t_env *env);
int		export_mult(char **cmd, t_env **env, t_all *all);
//int		valid_ft_close(infos->pipin);
	// ft_close(infos->pipout);
	// infos->pipin = -1;
	// infos->pipout = -1;env_line(char *line);

//dans unset.c
void	ft_unset(char **cmd, t_env **env, t_all *all);
void	env_remove_if(char *var, t_env **env, t_all *all);
void	valid_and_remove(char *var, t_env **env, t_all *all);
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
void	free_close_fds_pids(t_infos *info);
void	reset_in_out(t_infos *info);

//dans shlvl.c
t_env	*env_by_name(char *name, t_env *env);
int		lvl_incr(t_env *env);
void	increment_shlvl(t_env *env);

//dans no_pipe.c
void	no_pipe(t_all *all, t_env *env);

//dans pipe.c
void	if_signaled_pipes(int code);
void	pipe_wait(t_infos *info, int forks, int letswait);
int		malloc_pids_fds(t_infos *info);
int		file_success(t_all *all, int i, int forks);

//dans pipe2.c
void	parent(int **fds, int i, int n_pipe);
void	child(t_infos *info, int i);

//dans redir.c
int		open_file(t_all *all, char *red, int *fdin, int *fdout);
int		is_heredoc(char *red);

//dans pipe_loop.c
int		handle_redirections(t_all *all, int i, int *forks, int *letswait);
void	interrupted_heredoc(t_infos *info);
void	end_loop(t_infos *info, int forks, int letswait);

//dans redir2.c
void	ft_dup(t_infos *info);
int		assign_inout_handle_err(t_all *all);
int		handle_err_set_index(t_all *all, int *fdin, int *fdout, int i);

//dans open_file.c
int		open_out(char *red, int *fdout, char mode);
int		open_in(char *red, int *fdin);
int		get_inf_outf(t_all *all);

//dans utils2.c
void	free_resources_child(t_infos *info, t_env *env);
int		erreur(char type);
void	free_pids_fds_hdfs(t_infos *info);
int		env_size(t_env *env);

//dans heredoc.c
int		heredoc(t_all *all, char *red, int *fdin);
void	handle_signals(int sig);
void	sig_heredoc(int sig);
int		is_delim(char *input, char *eof);

//dans pipe_loop_eigentlich.c
void	loop(t_all *all);

//dans heredoc_pipes.c
int		hd_pipe_parent(t_all *all, int hd_i, char *eof);
int		open_heredoc_pipes(t_all *all, int *fdin);
void	end_heredoc(char *input, int line, char *eof);

//dans exit_refact.c
int		exit_error(t_infos *infos, int i);
void	exit_blabla(t_infos *info, int i);

//dans envp.c
char	**copy_envp(t_env *env);

#endif
// dsifhids fuidgsifsdgfugs fgdsu fgsugdf fugsdd
/*
variable error transcription:
1 = malloc error
2 = open quote error
3 = | error
4 = || error
5 = fds | error


liste de test:
|>$|
|>'$'|
|>"$"|
|>$''|
|>$""|
|>$USER|
|>'$USER'|
|>"$USER"|
|>$"USER"|
|>$'USER'|
|>$f|
|>"$f"|
|>'$f'|
|>$'f'|
|>$"f"|
|>$' '|
|>$" "|
|>$|
>$USER$USER
>$USER'$USER'
>$USER$U'SER'
>$USER'USER'
>$USER'$iUSER'
>$USER"$iUSER"
>"$DISPLAY$iUSER"
>"$DISPLAY"'$iUSER'
>"fsdds$USER"
>"$USER dsf"
>"$USER$USER"
>"$USER'USER'"
>"$USER""g"
>"$USER"'g'

s >dsf|">dfe" l
">fds" > l | ">fd"

regles:
1 -> si il y a un espace entre quotes ('' || "")
le nom du fichier est entour2 de '.
2 -> si il y a un $ entre quotes ('' || "") 
et qu'il est suivis de chara non alphanumerique 
a l'exception de _ le nom du fichier est entour2 de '
et le $ apparait
3 -> si il y a un $ entre quotes ("")
et qu'il est suivis de chara alphanumerique 
ou de _ ne correspondant a aucune variable
alors ces derniers plus le $ sont supprimes
(ex: >"$dsaf" - > || ; >"$fds f" -> |' f'| ;
>"$fdsa"fad -> |fad| ; >"d$fdsa" - > |d|)
4 -> si la chaine ne contient qu'un $
suivis d'un \0 alors le nom du fichier est entre '
(ex: >$ -> |'$'| ; >f$ -> |'f$'| ; >''$ -> |'$'|)
5 -> si un dollar est contenu entre des ',
il ne sera jamais converti
(ex: >'$USER' -> |'$USER'|)


*/

/*cbuyurha@paul-f4Ar6s4:~/Desktop/intra/minishell/test$ >' '$
cbuyurha@paul-f4Ar6s4:~/Desktop/intra/minishell/test$ ls
' $'  '$'
cbuyurha@paul-f4Ar6s4:~/Desktop/intra/minishell/test$ rm '$'
cbuyurha@paul-f4Ar6s4:~/Desktop/intra/minishell/test$ > "$'fds'"
cbuyurha@paul-f4Ar6s4:~/Desktop/intra/minishell/test$ ls
' $'  '$'\''fds'\'''
cbuyurha@paul-f4Ar6s4:~/Desktop/intra/minishell/test$ > "'fds'"
cbuyurha@paul-f4Ar6s4:~/Desktop/intra/minishell/test$ ls
' $'  '$'\''fds'\'''  "'fds'"
cbuyurha@paul-f4Ar6s4:~/Desktop/intra/minishell/test$ > "$"fds""
cbuyurha@paul-f4Ar6s4:~/Desktop/intra/minishell/test$ ls
' $'  '$'\''fds'\'''  '$fds'  "'fds'"
cbuyurha@paul-f4Ar6s4:~/Desktop/intra/minishell/test$ > '$"fds"'
cbuyurha@paul-f4Ar6s4:~/Desktop/intra/minishell/test$ ls
' $'  '$"fds"'	'$'\''fds'\'''	'$fds'	"'fds'"
*/