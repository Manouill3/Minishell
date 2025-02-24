/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:43:33 by tcybak            #+#    #+#             */
/*   Updated: 2025/02/24 18:21:55 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"


void	ft_init_list(t_list_char **lst)
{
	static int i = 1;

	if (i == 1)
	{
		*lst = NULL;
		i = 0;
	}
}

t_list_char *ft_lstnew_char(char *str, char *name)
{
    t_list_char *lst = malloc(sizeof(t_list_char));

    if (!lst)
        return NULL;
    lst->data = strdup(str);
    lst->next = NULL;
	lst->prev = NULL;
	lst->name = name;
    return lst;
}

void	ft_lstadd_back_char(t_list_char **lst, t_list_char *new)
{
	t_list_char	*tmp;

	ft_init_list(lst);
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