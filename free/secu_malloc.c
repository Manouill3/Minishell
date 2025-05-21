/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secu_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:54:38 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/21 15:08:51 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_mal	*ft_lstnew_mal(void *str)
{
	t_mal	*lst;

	lst = malloc(sizeof(t_mal));
	if (!lst)
		return (NULL);
	lst->content = str;
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_back_mal(t_mal **lst, t_mal *new)
{
	t_mal	*tmp;

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

void	ft_lstclear_mal(t_mal **lst)
{
	t_mal	*tmp;

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

void	ft_lstdelone_mal(t_mal *lst)
{
	if (!lst)
		return ;
	if (lst->content)
		free(lst->content);
    lst->content = NULL;
	free(lst);
    lst = NULL;
}

void    *add_malloc(t_mal *mal, size_t *size)
{
    void    *tmp;
    t_mal   *new;

    tmp = malloc(size);
    if (!tmp)
    {
        ft_lstclear_mal(&mal);
        exit (1);
    }
    new = ft_lstnew_mal(tmp);
    if (!new)
    {
        ft_lstclear_mal(&mal);
        exit (1);
    }
    ft_lstadd_back_mal(&mal, new);
    return (tmp);
}


