/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:20:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/08 18:50:18 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_heredoc_oef_before(t_init *param, t_heredoc *heredoc, int i,
		t_env *env)
{
	char	*final_eof;

	(void)param;
	ft_handle_heredoc_signals();
	while (1)
	{
		final_eof = get_final_eof(heredoc->eof[i]);
		heredoc->input = readline("heredoc> ");
		if (g_exit_code == 130)
		{
			if (heredoc->input)
				free(heredoc->input);
			free(final_eof);
			dup2(heredoc->fd_tmp, 0);
			close(heredoc->fd_tmp);
			free(final_eof);
			ft_handle_interrupt_signals();
			break ;
		}
		if (!ft_strchr(heredoc->eof[i], '"') && !ft_strchr(heredoc->eof[i], 39))
		{
			if (heredoc->input && ft_strchr(heredoc->input, '$'))
				heredoc->input = exp_heredoc(heredoc->input, env);
		}
		if (!heredoc->input || !ft_strcmp(heredoc->input, final_eof))
		{
			if (heredoc->input)
				free(heredoc->input);
			free(final_eof);
			break ;
		}
		free(final_eof);
		free(heredoc->input);
	}
	close(heredoc->fd_tmp);
}

void	ft_heredoc_oef_last(t_init *param, t_heredoc *heredoc, int i,
		t_env *env)
{
	char	*final_eof;

	(void)param;
	ft_handle_heredoc_signals();
	while (1)
	{
		final_eof = get_final_eof(heredoc->eof[i]);
		heredoc->input = readline("heredoc> ");
		if (g_exit_code == 130)
		{
			if (heredoc->input)
				free(heredoc->input);
			free(final_eof);
			dup2(heredoc->fd_tmp, 0);
			close(heredoc->fd_tmp);
			ft_handle_interrupt_signals();
			break ;
		}
		if (!ft_strchr(heredoc->eof[i], '"') && !ft_strchr(heredoc->eof[i], 39))
		{
			if (heredoc->input && ft_strchr(heredoc->input, '$'))
				heredoc->input = exp_heredoc(heredoc->input, env);
		}
		if (!heredoc->input || !ft_strcmp(heredoc->input, final_eof))
		{
			if (heredoc->input)
				free(heredoc->input);
			free(final_eof);
			break ;
		}
		ft_putendl_fd(heredoc->input, heredoc->fd);
		free(heredoc->input);
		free(final_eof);
	}
	close(heredoc->fd);
	close(heredoc->fd_tmp);
}

void	exec_heredoc(t_init *param, t_list_char *tmp, t_heredoc *heredoc,
		t_env *env)
{
	int	i;

	i = 0;
	if (heredoc->nb_eof > 0)
	{
		heredoc->name = get_name_h();
		heredoc->fd = open(heredoc->name, O_CREAT | O_WRONLY);
		get_eof_tab(tmp);
		heredoc->fd_tmp = dup(heredoc->fd);
		while (heredoc->eof[i])
		{
			if (heredoc->eof[i + 1] != NULL)
				ft_heredoc_oef_before(param, heredoc, i, env);
			else
				ft_heredoc_oef_last(param, heredoc, i, env);
			i++;
		}
	}
}
