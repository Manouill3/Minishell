/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:23:32 by marvin            #+#    #+#             */
/*   Updated: 2025/05/28 18:37:39 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == 3)
		g_exit_code = 131;
}

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_exit_code = 130;
	write(1, "\n", 1);
	close(0);
}

void	ft_handle_interrupt_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_handle_heredoc_signals(void)
{
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler_child(int sig)
{
	(void) sig;
}
