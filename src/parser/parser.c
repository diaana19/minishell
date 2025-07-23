/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lellanos <lellanos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:27:40 by lellanos          #+#    #+#             */
/*   Updated: 2025/07/22 12:42:47 by lellanos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_lex_token	*fill_cmd_fields(t_lex_token *lex, t_cmd *new_cmd)
{
	t_lex_token	*tmp;

	while (lex && lex->type != T_PIPE)
	{
		if (lex->type == T_WORD)
		{
			if (!add_to_argv(new_cmd, lex->value))
				return (NULL);
			lex = lex->next;
		}
		else
		{
			tmp = fill_redirections(lex, new_cmd);
			if (!tmp)
				return (NULL);
			lex = tmp;
		}
	}
	if (lex && lex->type == T_PIPE)
	{
		new_cmd->pipe_out = 1;
		lex = lex->next;
	}
	return (lex);
}

static int	empty_cmd_redir(t_cmd *new_cmd)
{
	if (new_cmd->argv == NULL && new_cmd->redir != NULL)
	{
		new_cmd->argv = malloc(sizeof(char *) * 1);
		if (!new_cmd->argv)
			return (0);
		new_cmd->argv[0] = NULL;
	}
	return (1);
}

static int	empty_cmd(t_lex_token *cur_lex, t_cmd **cmd_list, t_cmd *new_cmd)
{
	if (cur_lex == NULL && new_cmd->argv == NULL && new_cmd->redir == NULL)
	{
		free_cmd(new_cmd);
		free_cmd_list(cmd_list);
		return (0);
	}
	else
		return (1);
}

static void	set_pipe_built(t_cmd *prev_cmd, t_cmd *new_cmd)
{
	if (prev_cmd && prev_cmd->pipe_out == 1)
		new_cmd->pipe_in = 1;
	if (new_cmd->argv != NULL && is_built_in(new_cmd->argv[0]))
		new_cmd->is_builtin = 1;
}

void	parser(t_lex_token *lex, t_cmd **cmd_list)
{
	t_lex_token	*cur_lex;
	t_cmd		*new_cmd;
	t_cmd		*prev_cmd;

	new_cmd = NULL;
	prev_cmd = NULL;
	if (error_syntax(lex))
		return (free_cmd_plus_list(new_cmd, cmd_list));
	cur_lex = lex;
	while (cur_lex)
	{
		new_cmd = create_new_cmd();
		if (!new_cmd)
			return (free_cmd_plus_list(new_cmd, cmd_list));
		cur_lex = fill_cmd_fields(cur_lex, new_cmd);
		if (new_cmd->has_error)
			return (free_cmd_plus_list(new_cmd, cmd_list));
		if (!empty_cmd_redir(new_cmd) || !empty_cmd(cur_lex, cmd_list, new_cmd))
			return (free_cmd_plus_list(new_cmd, cmd_list));
		set_pipe_built(prev_cmd, new_cmd);
		prev_cmd = new_cmd;
		append_cmd_list(cmd_list, new_cmd);
	}
}
