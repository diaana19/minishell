/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lellanos <lellanos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:05:30 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/17 16:58:51 by lellanos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC
}						t_token_type;

typedef struct s_lex_token
{
	char				*value;
	t_token_type		type;
	int					quotes;
	struct s_lex_token	*next;
}						t_lex_token;

typedef struct s_parse_result
{
	int					i;
	char				*content;
	char				*error;
	int					quotes;
	t_token_type		type;
}						t_parse_re;

// Environment
typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

// builtins
typedef struct s_list
{
	char				*str;
	struct s_list		*prev;
	struct s_list		*next;
}						t_list;

/* append_output [ 0 > ]   [1 >> ]
	is_builtin [0 external] [1 built-in]
	int	pipe_in [0 no][ 1 yes]
	int pipe_out [0 no] [1 yes]
*/

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	int				heredoc_expand;
	struct s_redir	*next;
}	t_redir;

// CMD
typedef struct s_cmd
{
	char				**argv;
	t_redir				*redir;
	int					is_builtin;
	int					pipe_in;
	int					pipe_out;
	int					pipe_read;
	int					pipe_write;
	int					infile_fd;
	int					outfile_fd;
	int					has_error;
	struct s_cmd		*prev;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_data
{
	t_env				*env;
	int					exit_code;
	t_cmd				*cmds_list;
	int					pipe[2];
}						t_data;

#endif