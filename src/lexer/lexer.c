/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lellanos <lellanos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:34:28 by lellanos          #+#    #+#             */
/*   Updated: 2025/07/17 14:09:27 by lellanos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_create_token(t_parse_re partial, t_lex_token **lex)
{
	t_lex_token	*new_token;

	new_token = new_lex_token(partial.content, partial.type, partial.quotes);
	if (!new_token)
		return ;
	else
		ft_lstadd_back_lex(lex, new_token);
}

static int	ft_process_token(t_parse_re partial, int i, t_lex_token **lex)
{
	if (partial.i == -1)
	{
		printf("%s\n", partial.error);
		free_lex_token(lex);
		return (-1);
	}
	if (partial.i != i)
		ft_create_token(partial, lex);
	return (partial.i);
}

void	lexer(char *input, t_lex_token **lex_token_list, t_data data)
{
	int			i;
	t_parse_re	token_parse;

	i = 0;
	while (input[i])
	{
		while (input[i] == SPACE || input[i] == TAB)
			i++;
		if (input[i] == 0)
			return ;
		token_parse = ft_operator(input, i);
		i = ft_process_token (token_parse, i, lex_token_list);
		if (i == -1)
			return ;
		token_parse = ft_parameter(input, i, data);
		i = ft_process_token (token_parse, i, lex_token_list);
		if (i == -1)
			return ;
	}
}
