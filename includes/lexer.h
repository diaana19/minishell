/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lellanos <lellanos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:30:50 by lellanos          #+#    #+#             */
/*   Updated: 2025/07/17 19:20:00 by lellanos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structures.h"

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'
# define PIPE '|'
# define SPACE ' '
# define TAB '\t'
# define REDIRECT_IN 60
# define REDIRECT_OUT 62
//# define EOF 0    (No se puede definir EOF, ya esta reservado para stdio.h)

void		lexer(char *input, t_lex_token **lex_token_list, t_data data);
t_lex_token	*new_lex_token(char *value, t_token_type type, int quotes);
void		ft_lstadd_back_lex(t_lex_token **lst, t_lex_token *new);
void		free_lex_token(t_lex_token **lex_token_list);
int			read_until(char *input, char *charstop);
t_parse_re	ft_single_quotes(char *input, int i);
void		init_parse(t_parse_re *parse, int i);
t_parse_re	ft_parameter(char *input, int i, t_data data);
t_parse_re	str_until(char *input, int i, char *charstop);
t_parse_re	ft_double_quotes(char *input, int i, t_data data);
t_parse_re	get_var_name(char *input, int i, t_data data);
t_parse_re	ft_operator(char *input, int i);
char		*ft_strjoin_free(char *s1, char *s2);
void		add_redirection_back(t_redir **lst, t_redir *new);

#endif