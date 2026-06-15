#include "../includes/minishell.h"

static t_parse_re	ft_redirect_out(char *input, int i)
{
	t_parse_re	parse;

	init_parse(&parse, i);
	if (input[parse.i] == '>' && input[parse.i + 1] == '>')
	{
		parse.content = ft_strdup(">>");
		parse.type = T_APPEND;
		parse.i += 2;
	}
	else if (input[parse.i] == '>')
	{
		parse.content = ft_strdup(">");
		parse.type = T_REDIRECT_OUT;
		parse.i++;
	}
	return (parse);
}

static t_parse_re	ft_redirect_in(char *input, int i)
{
	t_parse_re	parse;

	init_parse(&parse, i);
	if (input[parse.i] == '<' && input[parse.i + 1] == '<')
	{
		parse.content = ft_strdup("<<");
		parse.type = T_HEREDOC;
		parse.i += 2;
	}
	else if (input[parse.i] == '<')
	{
		parse.content = ft_strdup("<");
		parse.type = T_REDIRECT_IN;
		parse.i++;
	}
	return (parse);
}

t_parse_re	ft_operator(char *input, int i)
{
	t_parse_re	parse;

	init_parse(&parse, i);
	if (input[parse.i] == '>')
		parse = ft_redirect_out(input, i);
	else if (input[parse.i] == '<')
		parse = ft_redirect_in(input, i);
	else if (input[parse.i] == '|')
	{
		parse.content = ft_strdup("|");
		parse.type = T_PIPE;
		parse.i++;
	}
	return (parse);
}