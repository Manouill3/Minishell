/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:48:49 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 22:48:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    close_all(t_init *param, t_list_char *tmp)
{
    if (tmp->fd_infile != -1)
        close (tmp->fd_infile);
    if (tmp->fd_outfile != -1)
        close (tmp->fd_outfile);
    if (param->fds.pipe_fd[0] != -1)
        close (param->fds.pipe_fd[0]);
    if (param->fds.pipe_fd[1] != -1)
        close (param->fds.pipe_fd[1]);
}

void	clear_files(t_list_char *lst)
{
	if (lst->heredoc->fd != -1)
		close(lst->heredoc->fd);
	if (lst->heredoc->name)
	{
		unlink(lst->heredoc->name);
		free(lst->heredoc->name);
		lst->heredoc->name = NULL;
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
		free (tab);
}

void	free_struct(t_init *param)
{
	ft_lstclear_env(&param->lst_env);
	ft_lstclear_env(&param->lst_export);
	free(param);
}

void	ft_free_all(t_init *param)
{
	t_list_char	*tmp;

	tmp = param->tok;
	while (tmp)
	{
		clear_files(tmp);
		//close_all(param, tmp);
		tmp = tmp->next;
	}
	if (param->tab)
	{
		free_tab(param->tab);
		param->tab = NULL;
	}
	if (param->tok)
	{
		ft_lstclear_char(&param->tok);
		param->tok = NULL;
	}
	if (param->line)
	{
		free(param->line);
		param->line = NULL;
	}
}
