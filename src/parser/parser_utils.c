/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:28:22 by lellanos          #+#    #+#             */
/*   Updated: 2025/07/18 20:25:44 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_built_in(char *cmd)
{
	char	*built_in[8];
	int		i;

	if (!cmd)
		return (0);
	i = 0;
	built_in[0] = "echo";
	built_in[1] = "cd";
	built_in[2] = "pwd";
	built_in[3] = "export";
	built_in[4] = "unset";
	built_in[5] = "env";
	built_in[6] = "exit";
	built_in[7] = NULL;
	while (built_in[i])
	{
		if (ft_strcmp(built_in[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	print_error_parser(const char *msg)
{
	printf ("minishell: %s \n", msg);
}

void	add_redirection_back(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
