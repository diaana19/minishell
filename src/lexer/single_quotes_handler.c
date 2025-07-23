/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leny <Leny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:41:24 by lellanos          #+#    #+#             */
/*   Updated: 2025/07/18 23:12:14 by Leny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_until(char *input, char *charstop)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (input[i])
	{
		j = 0;
		while (charstop[j])
		{
			if (input[i] == charstop[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

t_parse_re	str_until(char *input, int i, char *charstop)
{
	int			end;
	t_parse_re	parse;

	init_parse(&parse, i);
	end = read_until(&input[i], charstop);
	if (end == -1)
	{
		parse.error = "missing closing quotation";
		parse.i = -1;
	}
	else
	{
		parse.content = ft_strndup(&input[i], end);
		parse.i = i + end;
	}
	return (parse);
}

t_parse_re	ft_single_quotes(char *input, int i)
{
	t_parse_re	parse;

	init_parse(&parse, i);
	if (input[parse.i] != SINGLE_QUOTE)
		return (parse);
	parse = str_until(input, i + 1, "'");
	parse.quotes = 1;
	if (parse.i != -1)
	{
		if (input[parse.i] == SINGLE_QUOTE)
			parse.i++;
		else
		{
			parse.i = -1;
			parse.error = "minishell$ missing closing quotation";
		}
	}
	return (parse);
}
