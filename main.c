/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/11 13:59:35 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minishell.h"

int	ft_init(t_init **init)
{
	(*init) = malloc(sizeof(t_init));
	if (!(*init))
		return (1);
	(*init)->heredoc = malloc(sizeof(t_heredoc));
	if (!(*init)->heredoc)
	{
		free(init);
		return (1);
	}
	(*init)->heredoc->name = NULL;
	(*init)->heredoc->eof = NULL;
	return (0);
}

int main(int ac, char **av, char **env)
{
	t_init 	*init;

	if (ac == 1 && av[0] != NULL)
	{
		init = NULL;
		if (ft_init(&init))
			return(0);
		ft_handle_interrupt_signals();
		get_env(init, env);
		while(1)
		{
			init->pwd = get_pwd();
			init->line = readline(init->pwd);
			if (init->line == NULL)
			{
				ft_free(init);
				printf("exit\n");
				exit (1);	
			}
			if(init->line[0] != '\0')
			{
				add_history(init->line);
				ft_parsing_line(init, env);
				ft_free_all(init);
			}
		}
	}
}
