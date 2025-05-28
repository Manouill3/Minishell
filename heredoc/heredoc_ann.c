/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ann.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:58:25 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/28 17:17:46 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	handle_heredoc_input(t_heredoc *heredoc, char *final_eof)
{
	if (!heredoc->input || !ft_strcmp(heredoc->input, final_eof))
	{
		if (heredoc->input)
			free(heredoc->input);
		return (1);
	}
	return (0);
}
