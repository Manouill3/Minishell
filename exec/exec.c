/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:48:39 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/18 18:04:45 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	verif_build(t_list_char *lst)
{
	if(!ft_strcmp(lst->data, "echo"))
		printf("Je suis un built-in");
	if(!ft_strcmp(lst->data, "cd"))
		printf("Je suis un built-in");
	if(!ft_strcmp(lst->data, "pwd"))
		printf("Je suis un built-in");
	if(!ft_strcmp(lst->data, "export"))
		printf("Je suis un built-in");
	if(!ft_strcmp(lst->data, "unset"))
		printf("Je suis un built-in");
	if(!ft_strcmp(lst->data, "env"))
		printf("Je suis un built-in");
	if(!ft_strcmp(lst->data, "exit"))
		printf("Je suis un built-in");
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
void	ft_check_file(t_list_char *tok, t_fds *fds, t_tab_file *file)
{
	t_list_char *tmp;

	tmp = tok;
	fds->fd_infile = -1;
	fds->fd_outfile = -1;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "arg"))
		{
			if (!ft_strcmp(tmp->prev->data, "<"))
			{
				if (ft_strcmp(tmp->prev->prev->name, "cmd"))
				{
					tmp->next->name = "cmd";
				}	
				// if (access(tmp->data, R_OK | F_OK) != -1)
				// 	fds->fd_infile = open(tmp->data, O_RDONLY, 0644);
				else
					perror("infile");
			}
			if  (!ft_strcmp(tmp->prev->data, ">"))
			{
				if (ft_strcmp(tmp->prev->prev->name, "cmd"))
					tmp->next->name = "cmd";
				// if (access(tmp->data, F_OK | W_OK) != -1)
				// 	fds->fd_outfile = open(tmp->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				// else
				// {
					// if (access(tmp->data, F_OK) == -1)
					// 	fds->fd_outfile = open(tmp->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				// }
			}
			tmp = tmp->next;
		}
	}
}

void	ft_child_process(t_list_char *tok, t_fds *fds)
{
	t_list_char *tmp;

	tmp = tok;
	if ()
}

void	ft_fork(t_init *init)
{
	init->fds->pid = fork();
	if (param->fd.pid == -1)
    {
        perror("pid");
        exit (127);
    }
	if (param->fd.pid == 0)
		ft_child_process();
	else
		ft_parent_process();
}

void	ft_exec_cmd(t_init *init)
{
	ft_check_file(init->tok, init->fds);
	ft_count_cmd();
	if (init->fds->count_com != 1)
		ft_fork();
	verif_build();
}

// void	ft_exceve(t_init *init)
// {
// 	int		build;
// 	// int		fd_pid;
// 	// char	*data;
// 	t_list_char	*tmp;

// 	tmp = init->tok;
// 	build = 0;
// 	while(tmp)
// 	{
// 		build = verif_build(tmp);
// 		if (build == 0)
// 		{
			
// 			// ft_verif_file();
// 			// fd_pid = fork();
// 			// data = tmp->data;
			
// 		}
// 		tmp = tmp->next;
// 	}
// }