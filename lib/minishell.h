/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:52 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/12 17:11:25 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "libft/libft.h"

extern int	g_exit_code;

typedef struct s_fds
{
	int		pipe_fd[2];
	int		pid;
}			t_fds;

typedef struct s_heredoc
{
	int		fd;
	int		fd_tmp;
	int		nb_eof;
	char	*name;
	char	*input;
	char	**eof;
}			t_heredoc;

typedef struct s_env
{
	int				exp;
	char			*name;
	char			*cont;
	struct s_env	*next;
	struct s_env	*prev;
}			t_env;

typedef struct s_list_char
{
	int					len_cmd;
	int					fd_infile;
	int					fd_outfile;
	int					*ind_exp;
	char				**cmd_path;
	char				**cmd;
	char				**no_red;
	char				*funct;
	char				**infiles;
	struct s_heredoc	*heredoc;
	struct s_list_char	*next;
}			t_list_char;

typedef struct s_init
{
	int					i_ex;
	int					len_const_x;
	int					exist_x;
	int					create_x;
	int					status;
	int					count_cmd;
	char				*line;
	char				*pwd;
	char				*tmp_data;
	char				**tab;
	struct s_env		*lst_export;
	struct s_env		*lst_env;
	struct s_fds		fds;
	struct s_list_char	*tok;

}			t_init;

////////////////////////////////////////
///			main.c	                ///
//////////////////////////////////////

void		init_heredoc(t_list_char *node);
int			ft_init(t_init **init);
void		minishell(t_init *param, int tt_y);

////////////////////////////////////////
///			signal/signal.c         ///
//////////////////////////////////////

void		sigint_handler(int sig);
void		sigint_heredoc_handler(int sig);
void		ft_handle_interrupt_signals(void);
void		ft_handle_heredoc_signals(void);

////////////////////////////////////////
///			env/env.c	            ///
//////////////////////////////////////

void		get_final_cont(t_env *env);
void		get_final_cont_more(t_env *env);
void		get_name_env(t_env *env);
void		get_name_env_more(t_env *env);
int			get_env(t_init *param, char **env);

////////////////////////////////////////
///			lst/lst_funct_env.c	    ///
//////////////////////////////////////

t_env		*ft_lstnew_env(char *str);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
void		ft_lstclear_env(t_env **lst);
void		ft_lstdelone_env(t_env *lst);

////////////////////////////////////////
///			lst/lst_funct_char.c    ///
//////////////////////////////////////

t_list_char	*ft_lstnew_char(char **tab);
void		ft_lstadd_back_char(t_list_char **lst, t_list_char *new);
void		ft_lstclear_char(t_list_char **lst);
void		ft_lstdelone_char(t_list_char *lst);

////////////////////////////////////////
///			free/free_funct.c       ///
//////////////////////////////////////

void		close_all(t_init *param, t_list_char *tmp);
void		clear_files(t_list_char *lst);
void		free_tab(char **tab);
void		free_struct(t_init *param);
void		ft_free_all(t_init *param);

////////////////////////////////////////
///			utils/utils_fucnt.c     ///
//////////////////////////////////////

void		print_lst_env(t_env *lst);
void		print_lst_char(t_list_char *lst);
int			is_red(char *val);
int			ft_strcmp(char *s1, char *s2);
int			get_nb_cmd(char **tab);
int			only_white(char	*line);
int			nb_exp(char **cmd);

////////////////////////////////////////
///			parsing/token.c         ///
//////////////////////////////////////

int			ft_len_word(char *s, int start);
int			get_tab_len(char *tab);
t_list_char	*set_lst(int count_cmd);
void		set_cmd(char *tab, t_list_char *tmp);
void		get_token(t_init *param);

////////////////////////////////////////
///			parsing/parse_line.c    ///
//////////////////////////////////////

int			check_for_expand(t_list_char *tok, char **cmd, int *i);
void		get_funct_ann(t_list_char *tmp, int i);
void		get_funct(t_list_char *lst);
void		before_exec(t_init *param);
void		parsing_line(t_init *param);

////////////////////////////////////////
///		parsing/parse_utils.c    	///
//////////////////////////////////////

int			check_mixed_redir(t_init *param, char *line, int i);
int			check_too_many_redir(t_init *param, char *line, int i);
int			check_redir_no_file(t_init *param, char *line, int *i);
void		exec_supp(char **cmd, int i);
void		ft_supp_quote(t_list_char *tok, char **cmd);

////////////////////////////////////////
///	parsing/parse_syntax_error.c    ///
//////////////////////////////////////

int			check_redirections(t_init *param, char *line, int *i);
int			check_pipe_context(t_init *param, char *line, int *i);
int			check_double_pipes(t_init *param, char *line, int i);
int			check_quotes(char *line, int *i);
int			syntax_error(t_init *param, char *line);

////////////////////////////////////////
///			expand/expand.c         ///
//////////////////////////////////////

char		*get_result(char *cont, char *sub_word);
char		*check_quote(t_init *param, char *word, t_env *env);
char		**expand_input(t_init *param, char *word, char **inputs);
char		*expand_word(t_init *param, char *word);
void		expand_arg(t_init *param);

////////////////////////////////////////
///			expand/expand_res.c     ///
//////////////////////////////////////

char		**expand_input_q(t_init *param, char *word, char **inputs);
char		*check_quote_q(t_init *param, char *word, t_env *env);
char		*get_exit_value(t_init *param, char *word);
int			len_get_exit_value(int status, char *word);
int			final_len(char **inputs, int len);

////////////////////////////////////////
///			expand/expand_res2.c    ///
//////////////////////////////////////

char		*get_env_value(t_env *env, char *sub_word);
char		*expand_quote(t_init *param, char *word);
char		*get_actual_word_q(t_init *param, char *word, int i, int len);
char		*get_actual_word(t_init *param, char *word, int i, int len);
char		*one_char_test(t_init *param, char *word, char *sub_word, int i);

////////////////////////////////////////
///			expand/expand_res3.c    ///
//////////////////////////////////////

char		*get_final_input(char *res, char **inputs, int len);
void		handle_expand(t_init *param, t_list_char *tmp, int i, int *j);
char		*handle_double_quote(t_init *param, char *word);

////////////////////////////////////////
///			expand/expand_sup.c     ///
//////////////////////////////////////

int			inputs_len(char *word);
int			get_len_w_d(char *word, int i);
int			get_len_w_q(char *word, char quote, int i);
char		*all_quote_out(char *str);
char		*char_out(char *str, char c);

////////////////////////////////////////
///			expand/expand_heredoc.c ///
//////////////////////////////////////

int			count_quote(char *input);
char		*change_to_var(char *input, t_env *env);
char		*exp_heredoc(char *input, t_env *env);

////////////////////////////////////////
///			heredoc/heredoc.c       ///
//////////////////////////////////////

char		*get_valid_char(char *buffer);
char		*get_name_h(void);
void		get_nb_eof(t_list_char *tok);
void		get_eof_tab(t_list_char *tok);
char		*get_final_eof(char *str);

////////////////////////////////////////
///			heredoc/heredoc_exec.c  ///
//////////////////////////////////////

void		ft_heredoc_oef_before(t_heredoc *heredoc, int i, t_env *env);
int			handle_heredoc_interrupt_before(t_heredoc *heredoc,
				char *final_eof);
void		ft_heredoc_oef_last(t_heredoc *heredoc, int i, t_env *env);
int			handle_heredoc_input(t_heredoc *heredoc, t_env *env,
				char *final_eof, int i);
int			ft_handle_heredoc_interrupt(t_heredoc *heredoc, char *final_eof);
void		exec_heredoc(t_list_char *tmp, t_heredoc *heredoc, t_env *env);

////////////////////////////////////////
///			exec/exec_init.c		///
//////////////////////////////////////

int			verif_built(t_list_char *tok);
int			no_red_len(char **tab, t_list_char *tmp);
void		get_no_red(t_list_char *tok);
void		ft_exec_fork( t_list_char *tmp, t_init *param, int count);
void		exec(t_init *param);

////////////////////////////////////////
///			exec/exec_cmd.c	    	///
//////////////////////////////////////

void		child_process(t_list_char *tmp, t_init *param, int count);
void		parent_process(t_init *param);
void		ft_dup_file(t_init *param, t_list_char *tmp, int count);
void		exec_cmd(t_init *param, t_list_char *tmp);

////////////////////////////////////////
///			exec/exec_utils.c		///
//////////////////////////////////////

void		ft_wait_child(t_init *param);
char		**conv_lst_tab(t_env *env);
char		**make_path(t_env *env);
char		**set_args(char **args, char **path, t_init *param);
void		verif_fd(int count, t_init *param);

////////////////////////////////////////
///			exec/exec_file.c		///
//////////////////////////////////////

void		get_in_complet_list(t_list_char *node);
void		get_out_complet_list(t_list_char *node, int *i, int	*j);
void		get_in_out(t_list_char *tok);
void		get_good_fd(t_init *param, t_list_char *node);
void		get_in_fd(t_init *param, t_list_char *node, int i);
void		get_out_fd(t_init *param, t_list_char *node, int i);
void		check_access_out(t_list_char *node, int i);
void		check_access_app(t_list_char *node, int i);

////////////////////////////////////////
///			exec/exec_utils2.c		///
//////////////////////////////////////

void		get_tty(void);
char		*get_last_eof(char **cmd);
int			get_infile_nb(char **cmd);
int			get_outfile_nb(char **cmd);

////////////////////////////////////////
///			built-in.c/echo.c		///
//////////////////////////////////////

void		ft_echo(t_init *param, t_list_char *tok);

////////////////////////////////////////
///			built-in.c/pwd.c		///
//////////////////////////////////////

void		ft_exec_built_in(t_init *param, t_list_char *tok);
char		*get_pwd(void);
void		ft_pwd(void);

////////////////////////////////////////
///			built-in.c/cd.c			///
//////////////////////////////////////

void		ft_cd_rest(t_init *param, t_list_char *tok, char *path, int result);
void		ft_cd_alone(char *path, char **path_split,
				t_init *param, int result);
void		ft_cd(t_init *param, t_list_char *tok);

////////////////////////////////////////
///		built-in.c/cd_utils.c		///
//////////////////////////////////////

char		*ft_split_home_way(char **path_split, int i, int *j, char *lst);
char		*ft_give_home_way(char **path_split, char *lst);
char		*ft_path_user(char *path, t_list_char *tok);
int			check_inside_path(char *path, t_list_char *tok);
void		ft_cd_last(t_init *param, t_list_char *tok, int result, char *path);

////////////////////////////////////////
///			built-in.c/env.c		///
//////////////////////////////////////

void		ft_env(t_env *env);	

////////////////////////////////////////
///		built-in.c/export_add.c		///
//////////////////////////////////////

void		env_content(t_env *env, char *add);
void		export_content(t_env *exp, char *add);
int			existing_vars(t_env *env, t_env *exp, char *name, char *add);
int			add_to_env(t_init *param, char *name, char *add, t_list_char *tok);
void		add_to_both_lists(t_init *param, t_list_char *tok,
				char *add, char *name);
int			ft_add_value_var(t_init *param, int i, t_list_char *tok);

////////////////////////////////////////
///	built-in.c/export_add_utils.c	///
//////////////////////////////////////

void		ft_free_env(char *add, char *name);
void		env_content(t_env *env, char *add);
void		export_content(t_env *exp, char *add);

////////////////////////////////////////
///	built-in.c/export_var_utils.c	///
//////////////////////////////////////

void		ft_add_value(t_env *tmp_exp, t_env *tmp_env,
				char *new_const, t_init *param);
void		ft_alloc_new_const(t_list_char *tok, t_init *param,
				t_env *tmp_exp, t_env *tmp_env);
void		ft_rest_var(t_env *tmp_env, t_env *tmp_exp,
				t_init *param, t_list_char *tok);
void		ft_init_var(t_init *param);
int			ft_return_var(t_init *param, char *name);

////////////////////////////////////////
///	built-in.c/export_var.c			///
//////////////////////////////////////

int			ft_verif_exp(t_init *param, t_list_char *tok);
t_env		*ft_verif_env_create(t_env *tmp_env, char *name, t_init *param);
int			ft_existing_export(char	*name, t_env *tmp_exp,
				t_init *param, t_list_char *tok);
char		*ft_create_new_const(char *new_const, t_init *param,
				t_env *tmp_exp, t_env *tmp_env);
void		ft_create_var(t_init *param, t_list_char *tok, t_env *tmp_exp);

////////////////////////////////////////
///			built-in.c/export.c		///
//////////////////////////////////////

void		ft_export(t_init *param, t_list_char *tok);
void		ft_add_export_only(t_init *param, t_list_char *tok, t_env *tmp_exp);
void		ft_create_add_back(t_init *param, t_list_char *tok,
				t_env *tmp_exp, int exist);

////////////////////////////////////////
///			built-in.c/unset.c		///
//////////////////////////////////////

void		ft_unset(t_init *param, t_list_char *tok);

////////////////////////////////////////
///			built-in.c/exit.c		///
//////////////////////////////////////

void		ft_exit(t_init *param);

#endif