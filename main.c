/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/27 08:49:54 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minishell.h"

int main(int ac, char **av, char **env)
{
	t_init 	*init;

	if (ac == 1 && av[0] != NULL)
	{
		init = malloc(sizeof(t_init));
		if (init == NULL)
			return (0);
		while(1)
		{
			init->line = NULL;
			ft_handle_interrupt_signals();
			init->line = readline("Minishell:");
			add_history(init->line);
			ft_parsing_line(init, env);
			ft_check_order(init);
			if(ft_strcmp(init->line, "exit") == 0)
			{
				ft_free(init);
				rl_clear_history();
				exit(0);
			}
		}
	}
}
