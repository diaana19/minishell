/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 08:24:04 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/24 09:53:39 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_signal_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1); // Muy importante
	g_signal_pid = -3;
	rl_done = 1;
	rl_replace_line("", 0);
}

void	setup_heredoc_signals(void)
{
	struct sigaction sa_int;

	sa_int.sa_handler = heredoc_signal_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}