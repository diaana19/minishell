/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lellanos <lellanos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:24:53 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/23 21:48:52 by lellanos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "structures.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# define HEREDOC_TMP_FILE ".minishell_heredoc_tmp"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern volatile sig_atomic_t	g_signal_pid;

// builtins
int								ft_pwd(char **av);
int								ft_echo(char **args);
int								ft_cd(t_data *data, char **params);
int								handle_cd_home(t_data *data);
int								chdir_and_error(char *path);
void							update_pwd(t_data *data);
int								count_args(char **args);
bool							valid_id(char *str);
bool							exp_no_args(t_env *env);
bool							env_export(char *str, t_env **env);
int								key_exist(char *str, t_env *env);
bool							extract_name_value(char *str, char **var_name,
									char **var_value);
void							update_node(t_env *node, char *new_name,
									char *new_value);
bool							add_new_node(t_env **env, char *name,
									char *value);
int								ft_export(char **str, t_env **env);
int								ft_env(t_env *env, char **args);
void							ft_exit(t_data *data, char **args);
int								ft_unset(char **str, t_env **env);
// utils
void							sort_array(char **arr, int length);
char							*ft_strndup(const char *s1, size_t n);
char							*ft_strcpy(char *s1, const char *s2);
char							*ft_strcat(char *dest, char *src);
int								ft_strcmp(const char *s1, const char *s2);
void							free_total(t_data *data, int code);
int								strlen1(const char *s);
void							free_env_node(t_env *node);
void							free_arr(char **arr);
char							*get_env_value(const char *name, t_env *env);

// executor
int								input_builtin_parent(t_cmd *cmd);
int								output_builtin_parent(t_cmd *cmd);
char							*handle_empty_line(const char *line);
void							cleanup_buffers(char *readline_buf,
									char *expansion_buf);
void							write_buffer_to_fd(int fd, char *buffer);
void							print_eof_warning(char *word_delimiter);
char							*handle_expansion(char *buffer, t_data *data,
									bool expand_vars);
char							*process_dollar_loop(char *result,
									char *current_i, t_data *data);
bool							exec_pipe_cmds(t_data *data, t_cmd *first_cmd,
									int *temp_pipe_container, int cmd_count);
bool							process_input_redirs(t_cmd *cmd_node,
									t_data *data, int *temp_out_fd);
bool							handle_built_parent(t_data *data,
									t_cmd *cmd_node);
int								open_output_files_in_parent(t_cmd *cmd_node);
bool							open_redirections_in_parent(t_cmd *cmd_node,
									t_data *data);							
void							go_builtins(int save_stdin, int save_stdout,
									t_data *data, t_cmd *cmd);
bool							exec_builtin(t_data *data, t_cmd *cmd);
void							restore_std_fds(int sav_fd_stdin,
									int sav_fd_stdout);
bool							is_builtin(char *cmd);
bool							exec_cmds(t_data *data, t_cmd *cmd_node,
									int *pipe);
void							wait_child(t_data *data);
void							child_process(t_data *data, t_cmd *cmd,
									int *pipefd);
bool							execution(t_data *data);
bool							validate_cmd_path(char **cmd_path, t_data *data,
									char *cmd_name);
void							redirect_int_out(t_cmd *cmd_node,
									int *pip_fds_parent);
void							built_child(t_data *data, t_cmd *cmd_node,
									int *pipe);
void							handle_error_child(t_cmd *cmd_node);
void							cmd_exce_child(t_data *data, t_cmd *cmd_node,
									int *pip);
int								count_cmds(t_cmd *head);
char							*handle_path(t_data *data, char *cmd_name);
int								ft_path_join(char *dest, const char *path,
									const char *cmd, size_t dest_size);
char							*check_and_dup(t_data *data, char *cmd_name);
char							*find_cmd_path(t_data *data, char *cmd_name);
char							*get_path_value(t_env *env);
void							cmd_error(const char *cmd_name, int err_code);
bool							check_path(const char *cmd_path,
									const char *cmd_name, t_data *data);
char							*replace_dollar(const char *line, t_data *data);
int								here_doc(t_data *data, char *word_delimiter,
									bool expand_vars);

// ENVI
void							ft_copy_content(char *envp, t_env **env_list);
void							ft_copy_env(char **envp, t_env **env_list);
t_env							*new_env(char *name, char *value);
void							ft_lstadd_back_env(t_env **lst, t_env *new);
size_t							length_env_list(t_env *list);
char							**env_list_to_array(t_env *env);
void							free_env(t_env **env_list);
char							*duplicated_str(t_env *node, char *str_copy,
									bool is_name);
// SIGNALS
void							setup_signals(void);

void							run_shell(t_data *data);

// LENY BORRAR
// void		print_token(t_cmd *cmd_list);
void							print_cmd_list(t_cmd *token_list);
void							print_lex_token_list(
									t_lex_token *lex_token_lst);
const char						*get_token_type_str(t_token_type type);
void							print_copy_env(t_env *env_list);

void							close_all_pipes_in_parent(t_data *data);
#endif
