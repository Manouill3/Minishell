/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:15:48 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/28 18:33:14 by tcybak           ###   ########.fr       */
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

int	secu_cmd(t_list_char *tmp)
{
	if (tmp->len_cmd > 0 && tmp->len_ind_exp == tmp->len_cmd
		&& ft_strlen(tmp->cmd[0]) < 1)
		return (1);
	if (!ft_strcmp(tmp->cmd[0], ":"))
		return (1);
	return (0);
}

void	exec(t_init *param)
{
	t_list_char	*tmp;
	int			count;

	count = 0;
	tmp = param->tok;
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigint_handler_child);
	pipe_or_built(param, tmp, count);
	ft_wait_child(param);
	get_tty();
	ft_handle_interrupt_signals();
}
