/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:48:39 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/26 16:42:56 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	verif_build(t_list_char *lst)
{
	if(!ft_strcmp(lst->data, "echo"))
		return (1);
	if(!ft_strcmp(lst->data, "cd"))
		return (1);
	if(!ft_strcmp(lst->data, "pwd"))
		return (1);
	if(!ft_strcmp(lst->data, "export"))
		return (1);
	if(!ft_strcmp(lst->data, "unset"))
		return (1);
	if(!ft_strcmp(lst->data, "env"))
		return (1);
	if(!ft_strcmp(lst->data, "exit"))
		return (1);
	return (0);
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

void    handle_redirection(t_init *init)
{
	ft_check_file(init->tok, init->fds);
	ft_check_cmd(init->tok, init->env, init);
	check_access_input(init->fds);
	check_access_output(init->fds);
	
}

void	ft_exec_cmd(t_init *init)
{
	handle_redirection(init);
	ft_count_cmd(init->tok, init->fds);
	// if (init->fds->count_com != 1)
		// ft_fork();
	verif_build(init->tok);
	close_all(init->fds);
}
