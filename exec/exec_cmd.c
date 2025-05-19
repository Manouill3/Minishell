/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:10:20 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/19 16:32:17 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	child_process(t_list_char *tmp, t_init *param, int count)
{
	if (tmp->infiles)
		get_good_fd(param, tmp);
	if (param->status == 1 && tmp->infiles[0] != NULL)
	{
		close_all(param, tmp);
		exit (param->status);
	}
	if (count == 0)
	{
		dup2(tmp->fd_infile, STDIN_FILENO);
		if (tmp->fd_infile != -1)
			close(tmp->fd_infile);
	}
	ft_dup_file(param, tmp, count);
	close_all(param, tmp);
	exec_cmd(param, tmp);
}

void	parent_process(t_init *param)
{
	close(param->fds.pipe_fd[1]);
	dup2(param->fds.pipe_fd[0], STDIN_FILENO);
	close (param->fds.pipe_fd[0]);
}

void	built_in_fork(t_init *param, t_list_char *tmp)
{
	int		status;

	if (verif_built(tmp))
	{
		ft_exec_built_in(param, tmp);
		status = param->status;
		ft_free_all(param);
		free_struct(param);
		exit (status);
	}
}

void	exec_cmd(t_init *param, t_list_char *tmp)
{
	char	**path;
	char	**args;
	char	**env;

	built_in_fork(param, tmp);
	path = make_path(param->lst_env);
	args = set_args(tmp->no_red, path, param);
	env = conv_lst_tab(param->lst_env);
	if (!args || !args[0])
	{
		if (args)
			free_tab(args);
		free_tab(path);
		exit(param->status);
	}
	if (execve(args[0], args, env) == -1)
	{
		free_tab(path);
		free_tab(args);
		free_tab(env);
		if (!path)
			ft_putstr_fd(" command not found\n", 2);
		exit (param->status);
	}
}
