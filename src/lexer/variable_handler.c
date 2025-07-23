/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leny <Leny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:08:32 by lellanos          #+#    #+#             */
/*   Updated: 2025/07/18 23:12:18 by Leny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_var_value(char *var, t_data data)
{
	char	*value;

	value = ft_strdup("");
	while (data.env)
	{
		if (ft_strcmp(data.env->name, var) == 0)
		{
			free(value);
			value = ft_strdup(data.env->value);
		}
		data.env = data.env->next;
	}
	return (value);
}

static void	handle_env_var(t_parse_re *parse, char *input, t_data data)
{
	char	*tmp;

	*parse = str_until(input, parse->i, "'\" $<>|");
	if (parse->i == -1)
		return ;
	else if (ft_strcmp(parse->content, "") == 0)
	{
		free(parse->content);
		parse->content = ft_strdup("$");
	}
	else
	{
		tmp = parse->content;
		parse->content = get_var_value(tmp, data);
		free(tmp);
	}
}

static t_parse_re	handle_dolar_special(char *input, t_parse_re parse)
{
	char		*dolar_sign;
	char		*tmp;

	dolar_sign = ft_strdup("$");
	if (!dolar_sign)
	{
		parse.i = -1;
		return (parse);
	}
	parse = str_until(input, parse.i, "'\" $<>|");
	if (parse.i == -1)
	{
		free(dolar_sign);
		return (parse);
	}
	tmp = ft_strjoin_free(dolar_sign, parse.content);
	free(parse.content);
	parse.content = tmp;
	return (parse);
}

t_parse_re	get_var_name(char *input, int i, t_data data)
{
	t_parse_re	parse;

	init_parse(&parse, i);
	if (input[parse.i] != '$')
		return (parse);
	parse.i++;
	if (input[parse.i] == '?')
	{
		parse.content = ft_itoa(data.exit_code);
		parse.i++;
		return (parse);
	}
	if (!ft_isalnum(input[parse.i]) || input[parse.i] == '_')
		return (handle_dolar_special(input, parse));
	handle_env_var(&parse, input, data);
	return (parse);
}
