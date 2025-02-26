/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/26 16:52:17 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minishell.h"

int main(void)
{
	t_init 	*init;

	init = malloc(sizeof(t_init));
	if (init == NULL)
		return (0);
	while(1)
	{
		init->line = NULL;
		ft_handle_interrupt_signals();
		init->line = readline("Minishell:");
		add_history(init->line);
		ft_parsing_line(init);
		ft_check_order(init);
		if(ft_strcmp(init->line, "exit") == 0)
		{
			ft_free(init);
			rl_clear_history();
			exit(0);
		}
	}
}
