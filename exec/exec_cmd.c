/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:10:20 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/07 15:02:31 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    child_process(t_list_char *tmp, t_init *param, int count)
{
	if (tmp->infiles)
		get_good_fd(param, tmp);
	if (param->status == 1)
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

void    parent_process(t_init *param)
{
	close(param->fds.pipe_fd[1]);
	dup2(param->fds.pipe_fd[0], STDIN_FILENO);
	close (param->fds.pipe_fd[0]);
}

void    ft_dup_file(t_init *param, t_list_char *tmp, int count)
{
	if (param->count_cmd - 1 == count)
	{
		if (param->fds.pipe_fd[0] != -1)
			close(param->fds.pipe_fd[0]);
		if (param->fds.pipe_fd[1] != -1)
			close(param->fds.pipe_fd[1]);
		if (tmp->fd_infile != -1)
		{
			dup2(tmp->fd_infile, STDIN_FILENO);
			close(tmp->fd_infile);
		}
		if (tmp->fd_outfile != -1)
		{
			dup2(tmp->fd_outfile, STDOUT_FILENO);
			close(tmp->fd_outfile);
		}
		else
			dup2(param->fds.pipe_fd[1], STDOUT_FILENO);
	}
	else
	{
		if (param->fds.pipe_fd[0] != -1)
			close(param->fds.pipe_fd[0]);
		if (tmp->fd_outfile != -1)
		{
			dup2(tmp->fd_outfile, STDOUT_FILENO);
			close(tmp->fd_outfile);
		}
		else
			dup2(param->fds.pipe_fd[1], STDOUT_FILENO);
		if (param->fds.pipe_fd[1] != -1)
			close(param->fds.pipe_fd[1]);
	}
}

void    exec_cmd(t_init *param, t_list_char *tmp)
{
	char    **path;
	char    **args;
	char    **env;
	int		status;

	if (param->count_cmd > 0 && verif_built(tmp))
	{
		ft_exec_built_in(param, tmp);
		status = param->status;
		ft_free_all(param);
		free_struct(param);
		exit (status);
	}
	path = make_path(param->lst_env);
	if (!path)
		return ;
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
		exit (param->status);
	}
}
