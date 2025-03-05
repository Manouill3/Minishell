/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:12:50 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/04 14:53:54 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_heredoc(t_list_char *lst)
{
	t_list_char *tmp;

	tmp = lst;
	while(tmp)
	{
		if (!ft_strcmp(tmp->name, "Operator") && !ft_strcmp("<<", tmp->data))
		{
			if (!tmp->prev || ((ft_strcmp(tmp->prev->data, "cmd") && ft_strcmp(tmp->prev->data, "flag"))) || tmp->next == NULL)
				perror("heredoc");
			else
				printf("GOOD\n");
		}
		tmp = tmp->next;
	}
}