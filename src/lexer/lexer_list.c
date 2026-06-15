#include "../includes/minishell.h"

t_lex_token	*new_lex_token(char *value, t_token_type type, int quote_val)
{
	t_lex_token	*new;

	new = malloc(sizeof(t_lex_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->quotes = quote_val;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_lex(t_lex_token **lst, t_lex_token *new)
{
	t_lex_token	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}