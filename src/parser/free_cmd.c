#include "../includes/minishell.h"

static void	free_redirections(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_argv(char **argv)
{
	int	i;

	if (argv)
	{
		i = 0;
		while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->argv)
	{
		free_argv(cmd->argv);
	}
	if (cmd->redir)
	{
		free_redirections(cmd->redir);
	}
	free(cmd);
}

void	free_cmd_list(t_cmd **cmd_list)
{
	t_cmd	*tmp;

	if (!cmd_list)
		return ;
	while (*cmd_list)
	{
		tmp = (*cmd_list)->next;
		free_cmd(*cmd_list);
		*cmd_list = tmp;
	}
}

void	free_cmd_plus_list(t_cmd *cmd, t_cmd **cmd_list)
{
	if (cmd)
		free_cmd(cmd);
	if (cmd_list)
		free_cmd_list(cmd_list);
}