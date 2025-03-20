/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:48:39 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/20 13:39:50 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	verif_build(t_list_char *lst)
{
	if(!ft_strcmp(lst->data, "echo"))
		printf("Je suis un built-in\n");
	if(!ft_strcmp(lst->data, "cd"))
		printf("Je suis un built-in\n");
	if(!ft_strcmp(lst->data, "pwd"))
		printf("Je suis un built-in\n");
	if(!ft_strcmp(lst->data, "export"))
		printf("Je suis un built-in\n");
	if(!ft_strcmp(lst->data, "unset"))
		printf("Je suis un built-in\n");
	if(!ft_strcmp(lst->data, "env"))
		printf("Je suis un built-in\n");
	if(!ft_strcmp(lst->data, "exit"))
		printf("Je suis un built-in\n");
}

void	ft_count_cmd(t_list_char *tok , t_fds *fds)
{
	t_list_char *tmp;
	
	tmp = tok;
	fds->count_com = 0;
	while(tmp)
	{
		if (!ft_strcmp(tmp->name, "cmd"))
			fds->count_com++;
		tmp = tmp->next;
	}
}

void	ft_exec_cmd(t_init *init)
{
	handle_redirection(init->tok, init->fds);
	ft_count_cmd(init->tok, init->fds);
	// if (init->fds->count_com != 1)
		// ft_fork();
	verif_build(init->tok);
}
