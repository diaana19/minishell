/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:27:56 by lellanos          #+#    #+#             */
/*   Updated: 2025/07/18 20:23:41 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_parse_re	process_parse(char *input, t_parse_re parse)
{
	if (input[(parse).i] != DOUBLE_QUOTE)
	{
		(parse).i = -1;
		(parse).error = "minishell$ missing closing quotation";
	}
	else
		(parse).i++;
	return (parse);
}

static int	handle_partial(t_parse_re *parse, t_parse_re *partial)
{
	if (partial->i == -1)
		return (-1);
	parse->content = ft_strjoin_free(parse->content, partial->content);
	free(partial->content);
	parse->i = partial->i;
	return (0);
}

t_parse_re	ft_double_quotes(char *input, int i, t_data data)
{
	t_parse_re	parse;
	t_parse_re	partial;

	init_parse(&parse, i);
	init_parse(&partial, 0);
	if (input[parse.i] != DOUBLE_QUOTE)
		return (parse);
	parse.i++;
	while (input[parse.i] && input[parse.i] != DOUBLE_QUOTE)
	{
		partial = get_var_name(input, parse.i, data);
		if (handle_partial(&parse, &partial) == -1)
			return (partial);
		partial = str_until(input, parse.i, "\"$");
		partial.quotes = 1;
		if (handle_partial(&parse, &partial) == -1)
			return (partial);
		parse.quotes = (parse.quotes || partial.quotes);
	}
	return (process_parse(input, parse));
}
