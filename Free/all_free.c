/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:24:26 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/20 15:20:59 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	close_all(t_fds *fds)
{
	if (fds->fd_infile != -1)
		close(fds->fd_infile);
	if (fds->fd_outfile != -1)
		close(fds->fd_outfile);
}

void    ft_free(t_init *init)
{
	if (init->env)
		ft_lstclear_char(&init->env);
	if (init->line)
		free(init->line);
	if (init->heredoc)
		free(init->heredoc);
	if (init->fds)
		free(init->fds);
	if (init)
		free(init);
	return ;
}
	
void    ft_free_tab(char **tab)
{
	int i;
	
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

void    ft_free_all(t_init *init)
{
	if (init->line)
		free(init->line);
	if (init->tok)
		ft_lstclear_char(&init->tok);
	if (init->tab)
	{
		ft_free_tab(init->tab);
		init->tab = NULL;
	}
	if (init->heredoc->eof)
	{
		ft_free_tab(init->heredoc->eof);
		init->heredoc->eof = NULL;
	}
	if (init->fds->file_input)
	{
		free(init->fds->file_input);
		init->fds->file_input = NULL;
	}
	if (init->fds->file_output)
	{
		free(init->fds->file_output);
		init->fds->file_output = NULL;
	}	
}
