/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:23:32 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 19:23:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	sigint_handler(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handle_interrupt_signals(void)
{
	struct sigaction	sigint;

	ft_bzero(&sigint, sizeof(sigint));
	sigint.sa_handler = &sigint_handler;
	sigaction(SIGINT, &sigint, NULL);
	sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
}
