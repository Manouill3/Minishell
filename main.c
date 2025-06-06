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

int	g_exit_code = 0;

void	init_heredoc(t_list_char *node)
{
	node->heredoc->fd = -1;
	node->heredoc->eof = NULL;
	node->heredoc->input = NULL;
	node->heredoc->name = NULL;
	node->heredoc->nb_eof = 0;
}

void	minishell(t_init *param, int tt_y)
{
	while (1)
	{
		param->good_cd = 0;
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
		if (param->line && param->line[0] != '\0')
			add_history(param->line);
		parsing_line(param);
		free(param->line);
		if (param->tok)
			clear_files(param->tok);
		if (!tt_y)
			break ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_init	*param;
	int		tt_y;
	int		res;

	if (ac == 1 && av[0] != NULL)
	{
		param = malloc(sizeof(t_init));
		param->mal = ft_lstnew_mal(param);
		if (!param || !param->mal)
			return (0);
		param->tok = NULL;
		param->status = 0;
		ft_handle_interrupt_signals();
		get_env(param, env);
		if (param->lst_env == NULL)
			min_env(param);
		tt_y = isatty(STDIN_FILENO);
		minishell(param, tt_y);
		res = param->status;
		free_struct(param);
		return (res);
	}
}
