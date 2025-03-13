/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:48:39 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/13 17:58:19 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"


int	verif_build(t_list_char *lst)
{
	if(!ft_strcmp(lst->data, "echo"))
		return(1);
	if(!ft_strcmp(lst->data, "cd"))
		return(1);
	if(!ft_strcmp(lst->data, "pwd"))
		return(1);
	if(!ft_strcmp(lst->data, "export"))
		return(1);
	if(!ft_strcmp(lst->data, "unset"))
		return(1);
	if(!ft_strcmp(lst->data, "env"))
		return(1);
	if(!ft_strcmp(lst->data, "exit"))
		return(1);
	else
		return (0);
}

void	ft_exceve(t_init *init)
{
	int		build;
	// int		fd_pid;
	// char	*data;
	t_list_char	*tmp;

	tmp = init->tok;
	build = 0;
	while(tmp)
	{
		build = verif_build(tmp);
		if (build == 0)
		{
			
			// ft_verif_file();
			// fd_pid = fork();
			// data = tmp->data;
			
		}
		tmp = tmp->next;
	}
}
