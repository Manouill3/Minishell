/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/03 16:38:01 by mdegache         ###   ########.fr       */
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
		ft_handle_interrupt_signals();
		while(1)
		{
			init->line = readline("Minishell:");
			if (init->line == NULL)
				break ;
			add_history(init->line);
			ft_parsing_line(init, env);
			ft_check_order(init);
			if(ft_strcmp(init->line, "exit") == 0)
			{
				ft_free_tab(init->tab);
				ft_free(init);
				rl_clear_history();
				exit(0);
			}
		}
	}
}
