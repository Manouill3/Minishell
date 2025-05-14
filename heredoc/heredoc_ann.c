/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ann.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:58:25 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/14 15:27:40 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	handle_heredoc_input(t_heredoc *heredoc, t_env *env, char *final_eof, int i)
{
	if (!ft_strchr(heredoc->eof[i], '"') && !ft_strchr(heredoc->eof[i], 39))
	{
		printf("%s\n", heredoc->eof[i]);
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

int	handle_heredoc_interrupt_before(t_heredoc *heredoc, char *final_eof)
{
	if (g_exit_code == 130)
	{
		if (heredoc->input)
			free(heredoc->input);
		free(final_eof);
		dup2(heredoc->fd_tmp, 0);
		close(heredoc->fd_tmp);
		ft_handle_interrupt_signals();
		return (1);
	}
	return (0);
}
