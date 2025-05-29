/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funct_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:29:40 by marvin            #+#    #+#             */
/*   Updated: 2025/05/29 10:07:01 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_env	*ft_lstnew_env(char *str, t_mal *mal)
{
	t_env	*lst;

	lst = add_malloc(mal, sizeof(t_env));
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
