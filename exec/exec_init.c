/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:15:48 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/30 15:30:24 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	verif_built(t_list_char *tok)
{
	if(!ft_strcmp("echo", tok->funct))
		return (1);
	if(!ft_strcmp("cd", tok->funct))
		return (2);
	if(!ft_strcmp("pwd", tok->funct))
		return (3);
	if(!ft_strcmp("export", tok->funct))
		return (4);
	if(!ft_strcmp("unset", tok->funct))
		return (5);
	if(!ft_strcmp("env", tok->funct))
		return (6);
	if(!ft_strcmp("exit", tok->funct))
		return (7);
	return (0);
}

int	no_red_len(char **tab)
{
	int	i;
	int	len;
	
	i = 0;
	len = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], ">") && ft_strcmp(tab[i], "<"))
			len++;
		else
			i++;
		i++;
	}
	return (len);
}

void	get_no_red(t_list_char *tok)
{
	t_list_char *tmp;
	int	len;
	int	i;
	int	j;

	tmp = tok;
	while(tmp)
	{
		i = 0;
		j = 0;
		len = no_red_len(tok->cmd);
		tmp->no_red = ft_calloc(len + 1, sizeof(char *));
		if (!tok->no_red)
			return ;
		while (j < len && i < len_cmd(tok->cmd))
		{
			if (ft_strcmp(">", tok->cmd[i]) && ft_strcmp("<", tok->cmd[i]))
				tmp->no_red[j++] = ft_strdup(tok->cmd[i]);
			else
				i++;
			i++;
		}
		tmp = tmp->next;
	}
}

void    ft_exec_pipe(t_list_char *tmp, t_init *param, int count)
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

void    exec(t_init *param)
{
	t_list_char *tmp;
	int count;

	count = 0;
	tmp = param->tok;
	while (tmp)
	{
		if (tmp->infiles)
			get_in_fd(tmp);
		if (tmp->outfiles)
			get_out_fd(tmp);			
		if (param->count_cmd - 1 == count && (verif_built(tmp) == 5 || verif_built(tmp) == 7))
		{
			ft_exec_built_in(param, tmp);
		}
		if (pipe(param->fds.pipe_fd) == -1)
		{
			perror("pipe");
			exit (127);
		}
		ft_exec_pipe(tmp, param, count);
		close_all(param, tmp);
		count++;
		tmp = tmp->next;
	}
	ft_wait_child(param);
	get_tty();
}
