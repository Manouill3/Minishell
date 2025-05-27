/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:03:52 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/27 13:12:42 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_wait_child(t_init *param)
{
	int		status;
	int		sig;
	pid_t	last_pid;

	last_pid = wait(&status);
	while (last_pid > 0)
	{
		if (WIFEXITED(status) && last_pid == param->fds.pid)
			param->status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			sig = 128 + WTERMSIG(status);
			if (sig == 131)
				write(2, "Quit\n", 5);
			if (sig == 130)
				write(2, "\n", 1);
		}
		last_pid = wait(&status);
	}
}

char	**conv_lst_tab(t_env *env, t_mal *mal)
{
	int		i;
	char	*tmp_tab;
	t_env	*tmp;
	char	**tab;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tab = add_calloc(mal, i + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp_tab = ft_strjoin(tmp->name, "=", mal);
		tab[i++] = ft_strjoin(tmp_tab, tmp->cont, mal);
		tmp = tmp->next;
	}
	return (tab);
}

char	**make_path(t_env *env, t_mal *mal)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
			return (ft_normal_split(tmp->cont, ':', mal));
		tmp = tmp->next;
	}
	return (NULL);
}

void	verif_fd(int count, t_init *param)
{
	if (count == 0 && param->tok->fd_infile == -1)
		close_all(param, param->tok);
	if (count == param->count_cmd - 1 && param->tok->fd_outfile == -1)
		close_all(param, param->tok);
}
