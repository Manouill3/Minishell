/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/25 13:38:17 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minishell.h"

int main(void)
{
	t_init 	*init;

	init = malloc(sizeof(t_init));
	if (init == NULL)
		return (0);
	init->line = NULL;
	while(1)
	{
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
