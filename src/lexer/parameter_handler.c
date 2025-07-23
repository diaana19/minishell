/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:08:43 by lellanos          #+#    #+#             */
/*   Updated: 2025/07/18 20:24:21 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_parse(t_parse_re *parse, int i)
{
	parse->content = NULL;
	parse->error = NULL;
	parse->i = i;
	parse->type = -1;
	parse->quotes = 0;
}

static int	handle_partial(t_parse_re *parse, t_parse_re *partial)
{
	if (partial->i == -1)
		return (-1);
	parse->content = ft_strjoin_free(parse->content, partial->content);
	parse->quotes = (parse->quotes || partial->quotes);
	free(partial->content);
	parse->i = partial->i;
	return (0);
}

t_parse_re	ft_parameter(char *input, int i, t_data data)
{
	t_parse_re	parse;
	t_parse_re	partial;

	init_parse(&parse, i);
	while (input[parse.i] && input[parse.i] != SPACE && input[parse.i] != TAB
		&& input[parse.i] != '<' && input[parse.i] != '>'
		&& input[parse.i] != '|')
	{
		partial = ft_single_quotes(input, parse.i);
		if (handle_partial(&parse, &partial) == -1)
			return (free(partial.content), partial);
		partial = ft_double_quotes(input, parse.i, data);
		if (handle_partial(&parse, &partial) == -1)
			return (free(partial.content), partial);
		partial = get_var_name(input, parse.i, data);
		if (handle_partial(&parse, &partial) == -1)
			return (free(partial.content), partial);
		partial = str_until(input, parse.i, " '\"$<>|");
		if (handle_partial(&parse, &partial) == -1)
			return (free(partial.content), partial);
	}
	parse.type = T_WORD;
	return (parse);
}
