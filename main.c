/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/18 13:24:05 by tcybak           ###   ########.fr       */
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
		init->line = ft_strtrim(init->line, " ");
		add_history(init->line);
		if(ft_strcmp(init->line, "exit") == 0)
		{
			free(init->line);
			exit(0);
		}
	}
}
