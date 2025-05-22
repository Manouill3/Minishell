/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ann.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:58:25 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/21 14:49:26 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	handle_heredoc_input(t_heredoc *heredoc, t_env *env, char *final_eof, int i)
{
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
		return (1);
	}
	return (0);
}

int	handle_heredoc_interrupt_before(t_init *param, t_heredoc *heredoc, char *final_eof)
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
