/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leny <Leny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:41:41 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/16 14:46:48 by Leny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->is_builtin = 0;
	cmd->pipe_in = 0;
	cmd->pipe_out = 0;
	cmd->has_error = 0;
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	cmd->pipe_read = -1;
	cmd->pipe_write = -1;
	cmd->prev = NULL;
	cmd->next = NULL;
}

t_cmd	*create_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd(cmd);
	return (cmd);
}

void	append_cmd_list(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (*cmd_list == NULL)
		*cmd_list = new_cmd;
	else
	{
		last = *cmd_list;
		while (last->next != NULL)
			last = last->next;
		last->next = new_cmd;
		new_cmd->prev = last;
	}
}
