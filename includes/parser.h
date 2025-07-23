/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lellanos <lellanos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:05:36 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/22 12:43:24 by lellanos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

// PARSER
void		parser(t_lex_token *lex, t_cmd **cmd_list);

// FREE_CMD
void		free_cmd_list(t_cmd **cmd_list);
void		free_cmd(t_cmd *cmd);
void		free_argv(char **argv);
void		free_cmd_plus_list(t_cmd *cmd, t_cmd **cmd_list);

// UTILS
int			is_built_in(char *cmd);
void		print_error_parser(const char *msg);
int			error_syntax(t_lex_token *lex);

// CREATE CMD
void		init_cmd(t_cmd *cmd);
t_cmd		*create_new_cmd(void);
void		append_cmd_list(t_cmd **cmd_list, t_cmd *new_cmd);

// FILL ARGV
int			add_to_argv(t_cmd *cmd, const char *word);

// REDIRECTIONS
t_lex_token	*fill_redirections(t_lex_token *lex, t_cmd *cmd);

// Syntax validation
// int check_pipes(t_lex_token *lex);

#endif