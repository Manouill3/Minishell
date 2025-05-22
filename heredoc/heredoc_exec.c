/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:20:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/21 14:49:09 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_heredoc_oef_before(t_init *param, t_heredoc *heredoc, int i, t_env *env)
{
	char	*final_eof;
	(void) param;
	ft_handle_heredoc_signals();
	while (1)
	{
		final_eof = get_final_eof(heredoc->eof[i]);
		heredoc->input = readline("heredoc> ");
		if (handle_heredoc_interrupt_before(param, heredoc, final_eof))
			break ;
		if (handle_heredoc_input(heredoc, env, final_eof, i))
			break ;
		free(final_eof);
		free(heredoc->input);
	}
	close(heredoc->fd_tmp);
}

void	ft_heredoc_oef_last(t_init *param, t_heredoc *heredoc, int i, t_env *env)
{
	char	*final_eof;
	(void) param;
	ft_handle_heredoc_signals();
	while (1)
	{
		final_eof = get_final_eof(heredoc->eof[i]);
		heredoc->input = readline("heredoc> ");
		if (ft_handle_heredoc_interrupt(param, heredoc, final_eof))
			break ;
		if (handle_heredoc_input(heredoc, env, final_eof, i))
			break ;
		ft_putendl_fd(heredoc->input, heredoc->fd);
		free(heredoc->input);
		free(final_eof);
	}
	close(heredoc->fd);
	close(heredoc->fd_tmp);
}

int	ft_handle_heredoc_interrupt(t_init *param, t_heredoc *heredoc, char *final_eof)
{
	(void) param;
	if (g_exit_code == 130)
	{
		dup2(heredoc->fd_tmp, 0);
		close(heredoc->fd_tmp);
		ft_handle_interrupt_signals();
		if (heredoc->input)
			free(heredoc->input);
		free(final_eof);
		return (1);
	}
	return (0);
}

void	exec_heredoc(t_init *param, t_list_char *tmp, t_heredoc *heredoc, t_env *env)
{
	int	i;
	(void) param;
	i = 0;
	if (heredoc->nb_eof > 0)
	{
		heredoc->name = get_name_h();
		heredoc->fd = open(heredoc->name, O_CREAT | O_WRONLY);
		get_eof_tab(tmp);
		while (heredoc->eof[i])
		{
			heredoc->fd_tmp = dup(heredoc->fd);
			if (heredoc->eof[i + 1] != NULL)
				ft_heredoc_oef_before(param, heredoc, i, env);
			else
				ft_heredoc_oef_last(param, heredoc, i, env);
			i++;
		}
	}
}
