/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:48:49 by marvin            #+#    #+#             */
/*   Updated: 2025/05/30 09:35:53 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	close_all(t_init *param, t_list_char *tmp)
{
	if (tmp->fd_infile != -1)
		close(tmp->fd_infile);
	if (tmp->fd_outfile != -1)
		close(tmp->fd_outfile);
	if (param->fds.pipe_fd[0] != -1)
		close(param->fds.pipe_fd[0]);
	if (param->fds.pipe_fd[1] != -1)
		close(param->fds.pipe_fd[1]);
}

void	clear_files(t_list_char *lst)
{
	t_list_char	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->heredoc->fd != -1)
			close(tmp->heredoc->fd);
		if (tmp->heredoc->name)
			unlink(tmp->heredoc->name);
		tmp = tmp->next;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	free_struct(t_init *param)
{
	rl_clear_history();
	free(param->line);
	ft_lstclear_mal(&param->mal);
}
