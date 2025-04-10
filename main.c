/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:02:29 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 19:02:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minishell.h"

int	ft_init(t_init **param)
{
	(*param) = malloc(sizeof(t_init));
	if (!(*param))
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_init	*param;

	if (ac == 1 && av[0] != NULL)
	{
		param = NULL;
		if (ft_init(&param))
			return (0);
		ft_handle_interrupt_signals();
		if (get_env(param, env))
			return (0);
		while (1)
		{
			param->line = readline("Minishell : ");
			if (param->line == NULL)
			{
				free_struct(param);
				printf("exit\n");
				exit (1);
			}
			if (param->line[0] != '\0')
				add_history(param->line);
			parsing_line(param);
			ft_free_all(param);
		}
	}
}
