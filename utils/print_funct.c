/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:26:39 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/13 12:53:36 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	print_lst_env(t_env *lst)
{
	t_env	*curr;

	curr = lst;
	while (curr)
	{
		printf("name : %s\n", curr->name);
		printf("cont : %s\n", curr->cont);
		curr = curr->next;
	}
}

void	print_lst_char(t_list_char *lst)
{
	int			i;
	t_list_char	*curr;

	curr = lst;
	while (curr)
	{
		i = 0;
		while (curr->cmd[i])
		{
			printf("cmd[%d] : %s\n", i, curr->cmd[i]);
			i++;
		}
		i = 0;
		while (curr->no_red[i])
		{
			printf("no_red[%d] : %s\n", i, curr->no_red[i]);
			i++;
		}
		printf("funct : %s\n", curr->funct);
		curr = curr->next;
	}
}
