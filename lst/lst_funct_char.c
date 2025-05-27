/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funct_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:25:44 by marvin            #+#    #+#             */
/*   Updated: 2025/05/27 13:49:39 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_list_char	*ft_lstnew_char(char **tab, t_mal *mal)
{
	t_list_char	*lst;

	lst = add_malloc(mal, sizeof(t_list_char));
	lst->cmd_path = NULL;
	lst->cmd = tab;
	lst->no_red = NULL;
	lst->funct = NULL;
	lst->fd_infile = -1;
	lst->fd_outfile = -1;
	lst->infiles = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	lst->ind_exp = NULL;
	lst->heredoc = add_malloc(mal, sizeof(t_heredoc));
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
	new->prev = tmp;
}
