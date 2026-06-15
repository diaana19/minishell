#include "../includes/minishell.h"

static t_lex_token	*fill_redirect_heredoc(t_lex_token *lex, t_cmd *cmd)
{
	t_redir	*new;

	lex = lex->next;
	if (!lex || lex->type != T_WORD)
		return (NULL);
	new = malloc (sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = REDIR_HEREDOC;
	new->filename = ft_strdup(lex->value);
	if (lex->quotes == 0)
		new->heredoc_expand = 1;
	else
		new->heredoc_expand = 0;
	new->next = NULL;
	add_redirection_back(&cmd->redir, new);
	return (lex->next);
}

static t_lex_token	*fill_redirect_append(t_lex_token *lex, t_cmd *cmd)
{
	t_redir	*new;

	lex = lex->next;
	if (!lex || lex->type != T_WORD)
		return (NULL);
	new = malloc (sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = REDIR_APPEND;
	new->filename = ft_strdup(lex->value);
	new->heredoc_expand = 0;
	new->next = NULL;
	add_redirection_back(&cmd->redir, new);
	return (lex->next);
}

static t_lex_token	*fill_redirect_in(t_lex_token *lex, t_cmd *cmd)
{
	t_redir	*new;

	lex = lex->next;
	if (!lex || lex->type != T_WORD)
		return (NULL);
	new = malloc (sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = REDIR_IN;
	new->filename = ft_strdup(lex->value);
	new->heredoc_expand = 0;
	new->next = NULL;
	add_redirection_back(&cmd->redir, new);
	return (lex->next);
}

static t_lex_token	*fill_redirect_out(t_lex_token *lex, t_cmd *cmd)
{
	t_redir	*new;

	lex = lex->next;
	if (!lex || lex->type != T_WORD)
		return (NULL);
	new = malloc (sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = REDIR_OUT;
	new->filename = ft_strdup(lex->value);
	new->heredoc_expand = 0;
	new->next = NULL;
	add_redirection_back(&cmd->redir, new);
	return (lex->next);
}

t_lex_token	*fill_redirections(t_lex_token *lex, t_cmd *cmd)
{
	if (lex->type == T_REDIRECT_IN)
		return (fill_redirect_in(lex, cmd));
	else if (lex->type == T_REDIRECT_OUT)
		return (fill_redirect_out(lex, cmd));
	else if (lex->type == T_APPEND)
		return (fill_redirect_append(lex, cmd));
	else if (lex->type == T_HEREDOC)
		return (fill_redirect_heredoc(lex, cmd));
	return (lex);
}