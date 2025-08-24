/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:11:46 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/23 22:31:43 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal_pid = 0;

static int	signal_event(void)
{
	return (0);
}

// se activa cuando llega SIGINT o SIGQUIT
static void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_signal_pid == 0)
		{
			g_signal_pid = -1;
			rl_done = 1;
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_signal_pid > 0)
		{
			kill(g_signal_pid, SIGINT);
			ft_putstr_fd(STDOUT_FILENO, "\n");
		}
	}
	else if (signum == SIGQUIT)
	{
		if (g_signal_pid > 0)
		{
			ft_putstr_fd(STDOUT_FILENO, "Quit: 3\n");
			kill(g_signal_pid, SIGQUIT);
		}
	}
}

// configura las signals al inicio de la shell
void	setup_signals(void)
{
	rl_event_hook = signal_event;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
