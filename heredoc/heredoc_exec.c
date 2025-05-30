/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:20:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/30 09:06:19 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	ft_heredoc_oef_before(t_heredoc *heredoc, int i, t_env *env, t_mal *mal)
{
	char	*final_eof;

	ft_handle_heredoc_signals();
	while (g_exit_code != 130)
	{
		final_eof = get_final_eof(heredoc->eof[i], mal);
		heredoc->input = readline("heredoc> ");
		if (ft_handle_heredoc_interrupt(heredoc))
		{
			close(heredoc->fd);
			return (1);
		}
		if (!ft_strchr(heredoc->eof[i], '"') && !ft_strchr(heredoc->eof[i], 39))
		{
			if (heredoc->input && ft_strchr(heredoc->input, '$'))
				heredoc->input = exp_heredoc(heredoc->input, env, mal);
		}
		if (handle_heredoc_input(heredoc, final_eof))
			break ;
		free(heredoc->input);
	}
	close(heredoc->fd);
	close(heredoc->fd_tmp);
	return (0);
}

int	ft_heredoc_oef_last(t_heredoc *heredoc, int i, t_env *env, t_mal *mal)
{
	char	*final_eof;

	ft_handle_heredoc_signals();
	while (g_exit_code != 130)
	{
		final_eof = get_final_eof(heredoc->eof[i], mal);
		heredoc->input = readline("heredoc> ");
		if (ft_handle_heredoc_interrupt(heredoc))
		{
			close(heredoc->fd);
			return (1);
		}
		if (!ft_strchr(heredoc->eof[i], '"') && !ft_strchr(heredoc->eof[i], 39))
		{
			if (heredoc->input && ft_strchr(heredoc->input, '$'))
				heredoc->input = exp_heredoc(heredoc->input, env, mal);
		}
		if (handle_heredoc_input(heredoc, final_eof))
			break ;
		ft_putendl_fd(heredoc->input, heredoc->fd);
		free(heredoc->input);
	}
	close(heredoc->fd);
	close(heredoc->fd_tmp);
	return (0);
}

int	ft_handle_heredoc_interrupt(t_heredoc *heredoc)
{
	if (g_exit_code == 130)
	{
		if (heredoc->input)
			free(heredoc->input);
		dup2(heredoc->fd_tmp, 0);
		close(heredoc->fd_tmp);
		ft_handle_interrupt_signals();
		return (1);
	}
	return (0);
}

void	exec_heredoc(t_list_char *tmp, t_heredoc *heredoc,
	t_env *env, t_mal *mal)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (heredoc->nb_eof > 0)
	{
		heredoc->name = get_name_h(mal);
		get_eof_tab(tmp, mal);
		while (heredoc->eof[i])
		{
			heredoc->fd = open(heredoc->name, O_CREAT
					| O_WRONLY | O_TRUNC, 0644);
			heredoc->fd_tmp = dup(0);
			if (heredoc->eof[i + 1] != NULL)
				j = ft_heredoc_oef_before(heredoc, i, env, mal);
			else
				j = ft_heredoc_oef_last(heredoc, i, env, mal);
			i++;
			if (j == 1)
				break ;
		}
	}
}
