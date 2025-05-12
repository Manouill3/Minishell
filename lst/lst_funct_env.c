/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funct_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:29:40 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 20:29:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_env	*ft_lstnew_env(char *str)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->name = NULL;
	lst->cont = str;
	lst->next = NULL;
	lst->prev = NULL;
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

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

void	ft_lstclear_env(t_env **lst)
{
	t_env	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_env(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_lstdelone_env(t_env *lst)
{
	if (!lst)
		return ;
	if (lst->cont)
		free(lst->cont);
	if (lst->name)
		free(lst->name);
	free(lst);
}
