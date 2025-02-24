/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:43:33 by tcybak            #+#    #+#             */
/*   Updated: 2025/02/24 16:42:51 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_list_char *ft_lstnew_char(char *str)
{
    t_list_char *lst = malloc(sizeof(t_list_char));

    if (!lst)
        return NULL;
    lst->data = strdup(str);
    lst->next = NULL;
    return lst;
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