/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:20:27 by lellanos          #+#    #+#             */
/*   Updated: 2025/07/23 12:54:07 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_string_array(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_lex_token(t_lex_token **lex_token_list)
{
	t_lex_token	*tmp;

	if (!lex_token_list || !*lex_token_list)
		return ;
	while (*lex_token_list)
	{
		tmp = (*lex_token_list)->next;
		free((*lex_token_list)->value);
		free((*lex_token_list));
		*lex_token_list = tmp;
	}
	*lex_token_list = NULL;
}
