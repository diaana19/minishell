#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

void		parser(t_lex_token *lex, t_cmd **cmd_list);
void		free_cmd_list(t_cmd **cmd_list);
void		free_cmd(t_cmd *cmd);
void		free_argv(char **argv);
void		free_cmd_plus_list(t_cmd *cmd, t_cmd **cmd_list);
int			is_built_in(char *cmd);
void		print_error_parser(const char *msg);
int			error_syntax(t_lex_token *lex);
void		init_cmd(t_cmd *cmd);
t_cmd		*create_new_cmd(void);
void		append_cmd_list(t_cmd **cmd_list, t_cmd *new_cmd);
int			add_to_argv(t_cmd *cmd, const char *word);
t_lex_token	*fill_redirections(t_lex_token *lex, t_cmd *cmd);

#endif