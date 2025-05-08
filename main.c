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

int g_exit_code = 0;

void	init_heredoc(t_list_char *node)
{
	node->heredoc->fd = -1;
	node->heredoc->eof = NULL;
	node->heredoc->input = NULL;
	node->heredoc->name = NULL;
	node->heredoc->nb_eof = 0;
}

int	ft_init(t_init **param)
{
	(*param) = malloc(sizeof(t_init));
	if (!(*param))
		return (1);
	(*param)->status = 0;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_init	*param;
	int		tt_y;
	int		res;

	if (ac == 1 && av[0] != NULL)
	{
		param = NULL;
		if (ft_init(&param))
			return (0);
		ft_handle_interrupt_signals();
		if (get_env(param, env))
			return (0);
		tt_y = isatty(STDIN_FILENO);
		while (1)
		{
			param->line = readline("Minishell : ");
			if (param->line == NULL)
			{
				printf("exit\n");
				break ;
			}
			if (g_exit_code == 130)
			{
				param->status = g_exit_code;
				g_exit_code = 0;
			}
			if (param->line[0] != '\0')
			add_history(param->line);
			parsing_line(param);
			ft_free_all(param);
			if (!tt_y)
				break;
		}
		res = param->status;
		free_struct(param);
		return (res);
	}
}
