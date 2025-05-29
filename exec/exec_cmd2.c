/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:25:16 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/29 16:45:14 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_dup_file_ann(t_init *param, t_list_char *tmp)
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

void	ft_dup_file(t_init *param, t_list_char *tmp, int count)
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
		ft_dup_file_ann(param, tmp);
}

char	**basic_args(char **tab, t_mal *mal)
{
	int		i;
	int		len;
	char	**args;

	len = 0;
	i = 0;
	while (tab[len])
		len++;
	args = add_calloc(mal, len + 1, sizeof(char *));
	while (tab[i])
	{
		args[i] = ft_strdup(tab[i], mal);
		i++;
	}
	return (args);
}

void	fail_execve(char **args, char **path,
		char **env, t_init *param)
{
	int		status;

	(void)args;
	(void)path;
	(void)env;
	status = param->status;
	if (!path)
		ft_putstr_fd("command not found\n", 2);
	ft_lstclear_mal(&param->mal);
	exit (status);
}
