/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:50:24 by dirituay          #+#    #+#             */
/*   Updated: 2025/08/24 19:42:45 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_done = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_pid = 1;
	}
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

// Restaurar señales normales
void	restore_default_signals(void)
{
	setup_signals();
}
