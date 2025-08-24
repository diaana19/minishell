/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:24:53 by dirituay          #+#    #+#             */
/*   Updated: 2025/08/24 19:49:19 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <stdio.h>
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
void							close_all_pipes_in_parent(t_data *data);
void							close_parent_pipes(int prev_read_fd,
									int *pipe_fds);

// executor
bool							handle_pipe_error(t_data *data,
									int prev_read_fd);
void							setup_pipes_and_fork(t_data *data, t_cmd *cmd,
									int *prev_read_fd, int *pipe_fds);
int								process_input_redirect(t_redir *redir,
									t_data *data, int *final_fd);
bool							has_output_redir(t_redir *redir);
bool							has_input_redir(t_redir *redir);
void							close_inherited_pipes(int *pips_fds,
									t_cmd *cmd_node);
void							parent_process(t_cmd *cmd_node);
char							*validate_and_get_path(t_data *data,
									char *cmd_name);
char							*join_path_and_cmd(const char *path,
									const char *cmd);
int								handle_all_redirections(t_cmd *cmd_node,
									t_data *data, int *pipe_fds);
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
int								handle_input_redirec(t_cmd *cmd_node,
									t_data *data);
int								handle_output_redirec(t_cmd *cmd_node);
void							go_builtins(int save_stdin, int save_stdout,
									t_data *data, t_cmd *cmd);
bool							execution_builtins(t_data *data, t_cmd *cmd);
void							restore_fds_parent(int sav_fd_stdin,
									int sav_fd_stdout);
bool							is_builtin(char *cmd);
void							wait_child(t_data *data, int num_cmds);
void							child_process(t_data *data, t_cmd *cmd,
									int prev_read_fd, int *pipefd);
bool							execution(t_data *data);
void							built_child(t_data *data, t_cmd *cmd_node,
									int *pipe);
int								count_cmds(t_cmd *head);
char							*get_path_value(t_env *env);
void							cmd_error(const char *cmd_name, int err_code);
char							*replace_dollar(const char *line, t_data *data);
int								here_doc(t_data *data, char *word_delimiter,
									bool expand_vars);

// environment
void							ft_copy_content(char *envp, t_env **env_list);
void							ft_copy_env(char **envp, t_env **env_list);
t_env							*new_env(char *name, char *value);
void							ft_lstadd_back_env(t_env **lst, t_env *new);
size_t							length_env_list(t_env *list);
char							**env_list_to_array(t_env *env);
void							free_env(t_env **env_list);
char							*duplicated_str(t_env *node, char *str_copy,
									bool is_name);
// signals
void							setup_signals(void);
void							setup_heredoc_signals(void);
void							restore_default_signals(void);
void							run_shell(t_data *data);

#endif
