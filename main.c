/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/05 15:30:00 by mdegache         ###   ########.fr       */
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
			{
				ft_free(init);
				printf("exit\n");
				exit (1);	
			}
			add_history(init->line);
			ft_parsing_line(init, env);
			ft_check_order(init);
			ft_free_all(init);
		}
	}
}
