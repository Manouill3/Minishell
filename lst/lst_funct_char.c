/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funct_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:25:44 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 20:25:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_list_char	*ft_lstnew_char(char **tab)
{
	t_list_char	*lst;

	lst = malloc(sizeof(t_list_char));
	if (!lst)
		return (NULL);
	lst->cmd_path = NULL;
	lst->cmd = tab;
	lst->no_red = NULL;
	lst->funct = NULL;
	lst->fd_infile = -1;
	lst->fd_outfile = -1;
	lst->infiles = NULL;
	lst->outfiles = NULL;
	lst->next = NULL;
	lst->heredoc = malloc(sizeof(t_heredoc));
	if (!lst->heredoc)
		return (NULL);
	init_heredoc(lst);
	return (lst);
}

void	ft_lstadd_back_char(t_list_char **lst, t_list_char *new)
{
	t_list_char	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lstclear_char(t_list_char **lst)
{
	t_list_char	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_char(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_lstdelone_char(t_list_char *lst)
{
	if (!lst)
		return ;
	if (lst->heredoc->eof)
		free_tab(lst->heredoc->eof);
	if (lst->heredoc)
		free(lst->heredoc);
	if (lst->infiles)
		free_tab(lst->infiles);
	if (lst->outfiles)
		free_tab(lst->outfiles);
	if (lst->no_red)
		free_tab(lst->no_red);
	if (lst->cmd)
		free_tab(lst->cmd);
	if (lst->funct)
		free(lst->funct);
	free(lst);
}
