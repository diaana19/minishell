#include "../includes/minishell.h"

static int	print_error_syntax(char c)
{
	printf("minishell$ syntax error near unexpected token '%c'\n", c);
	return (1);
}

static int	check_redirect_out(t_lex_token *lex)
{
	while (lex)
	{
		if (lex->type == T_REDIRECT_OUT || lex->type == T_APPEND)
		{
			if (lex->next == NULL || lex->next->type != T_WORD)
				return (1);
		}
		lex = lex->next;
	}
	return (0);
}

static int	check_redirect_in(t_lex_token *lex)
{
	while (lex)
	{
		if (lex->type == T_REDIRECT_IN || lex->type == T_HEREDOC)
		{
			if (lex->next == NULL || lex->next->type != T_WORD)
				return (1);
		}
		lex = lex->next;
	}
	return (0);
}

static int	check_pipes(t_lex_token *lex)
{
	if (lex->type == T_PIPE)
		return (1);
	while (lex)
	{
		if (lex->type == T_PIPE)
		{
			if (lex->next == NULL || lex->next->type != T_WORD)
				return (1);
		}
		lex = lex->next;
	}
	return (0);
}

int	error_syntax(t_lex_token *lex)
{
	if (!lex)
		return (0);
	if (check_pipes(lex))
		return (print_error_syntax('|'));
	if (check_redirect_in(lex))
		return (print_error_syntax('<'));
	if (check_redirect_out(lex))
		return (print_error_syntax('>'));
	return (0);
}
