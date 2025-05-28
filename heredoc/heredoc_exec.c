/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:20:05 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/28 15:31:07 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_heredoc_oef_before(t_heredoc *heredoc, int i, t_env *env, t_mal *mal)
{
	char	*final_eof;

	ft_handle_heredoc_signals();
	while (1)
	{
		final_eof = get_final_eof(heredoc->eof[i], mal);
		heredoc->input = readline("heredoc> ");
		if (handle_heredoc_interrupt_before(heredoc))
			break ;
		if (!ft_strchr(heredoc->eof[i], '"') && !ft_strchr(heredoc->eof[i], 39))
		{
			if (heredoc->input && ft_strchr(heredoc->input, '$'))
				heredoc->input = exp_heredoc(heredoc->input, env, mal);
		}
		if (handle_heredoc_input(heredoc, final_eof))
			break ;
		free(heredoc->input);
	}
	close(heredoc->fd_tmp);
}

void	ft_heredoc_oef_last(t_heredoc *heredoc, int i, t_env *env, t_mal *mal)
{
	char	*final_eof;

	ft_handle_heredoc_signals();
	while (1)
	{
		final_eof = get_final_eof(heredoc->eof[i], mal);
		heredoc->input = readline("heredoc> ");
		if (ft_handle_heredoc_interrupt(heredoc))
			break ;
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
}

int	ft_handle_heredoc_interrupt(t_heredoc *heredoc)
{
	if (g_exit_code == 130)
	{
		printf("heredoc->fd_tmp = %d\n", heredoc->fd_tmp);
		printf("heredoc->fd = %d\n", heredoc->fd);
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

	i = 0;
	if (heredoc->nb_eof > 0)
	{
		heredoc->name = get_name_h(mal);
		heredoc->fd = open(heredoc->name, O_CREAT | O_WRONLY);
		get_eof_tab(tmp, mal);
		while (heredoc->eof[i])
		{
			heredoc->fd_tmp = dup(heredoc->fd);
			printf("heredoc->fd_tmp = %d\n", heredoc->fd_tmp);
			printf("heredoc->fd = %d\n", heredoc->fd);
			if (heredoc->eof[i + 1] != NULL)
				ft_heredoc_oef_before(heredoc, i, env, mal);
			else
				ft_heredoc_oef_last(heredoc, i, env, mal);
			i++;
		}
	}
}
