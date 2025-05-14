/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:15:48 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/14 14:06:25 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	verif_built(t_list_char *tok)
{
	if (!ft_strcmp(tok->funct, "echo"))
		return (1);
	if (!ft_strcmp(tok->funct, "cd"))
		return (2);
	if (!ft_strcmp(tok->funct, "pwd"))
		return (3);
	if (!ft_strcmp(tok->funct, "export"))
		return (4);
	if (!ft_strcmp(tok->funct, "unset"))
		return (5);
	if (!ft_strcmp(tok->funct, "env"))
		return (6);
	if (!ft_strcmp(tok->funct, "exit"))
		return (7);
	return (0);
}

void	ft_exec_fork(t_list_char *tmp, t_init *param, int count)
{
	param->fds.pid = fork();
	if (param->fds.pid == -1)
	{
		perror("pid");
		exit (127);
	}
	if (param->fds.pid == 0)
		child_process(tmp, param, count);
	else
		parent_process(param);
}

int	ft_exec_pipe(t_list_char *tmp, t_init *param, int count)
{
	if (pipe(param->fds.pipe_fd) == -1)
	{
		perror("pipe");
		exit (127);
	}
	ft_exec_fork(tmp, param, count);
	close_all(param, tmp);
	count++;
	return (count);
}

void	exec(t_init *param)
{
	t_list_char	*tmp;
	int			count;

	count = 0;
	tmp = param->tok;
	while (tmp)
	{
		if (tmp->len_cmd == 0)
		{
			param->status = 127;
			tmp = tmp->next;
			continue ;
		}
		if ((verif_built(tmp) == 2 || verif_built(tmp) == 4
				|| verif_built(tmp) == 5 || verif_built(tmp) == 7))
		{
			ft_exec_built_in(param, tmp);
			tmp = tmp->next;
			continue ;
		}
		count = ft_exec_pipe(tmp, param, count);
		tmp = tmp->next;
	}
	ft_wait_child(param);
	get_tty();
}
