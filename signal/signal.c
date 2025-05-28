/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:23:32 by marvin            #+#    #+#             */
/*   Updated: 2025/05/28 16:21:00 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	sigint_handler(int sig)
{
	if (sig == 2)
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
	rl_replace_line("", 0);
	rl_done = 1;
	close(0);
}

void	ft_handle_interrupt_signals(void)
{
	struct sigaction	sigint;

	ft_bzero(&sigint, sizeof(sigint));
	sigint.sa_handler = &sigint_handler;
	sigaction(SIGINT, &sigint, NULL);
	sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
}

void	ft_handle_heredoc_signals(void)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof(sig));
	sig.sa_handler = &sigint_heredoc_handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
}

void	sigint_handler_child(int sig)
{
	(void) sig;
}
