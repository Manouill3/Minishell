/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:21:52 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/08 11:22:41 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	get_in_out_complet_list(t_list_char *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < node->len_cmd)
	{
		while (node->cmd[i] && ft_strlen(node->cmd[i]) <= 0)
			i++;
		if (!ft_strcmp(node->cmd[i], "<") && node->cmd[i + 1] )
		{
			node->infiles[j++] = ft_strdup(node->cmd[i++]);
			node->infiles[j++] = ft_strdup(node->cmd[i]);
		}
		if (!ft_strcmp(node->cmd[i], "<<") && node->cmd[i + 1] )
		{
			node->infiles[j++] = ft_strdup(node->cmd[i++]);
			node->infiles[j++] = ft_strdup(node->cmd[i]);
		}
		if (!ft_strcmp(node->cmd[i], ">") && node->cmd[i + 1])
		{
			node->infiles[j++] = ft_strdup(node->cmd[i++]);
			node->infiles[j++] = ft_strdup(node->cmd[i]);
		}
		if (!ft_strcmp(node->cmd[i], ">>") && node->cmd[i + 1])
		{
			node->infiles[j++] = ft_strdup(node->cmd[i++]);
			node->infiles[j++] = ft_strdup(node->cmd[i]);
		}
		i++;
	}
}

void	get_in_out(t_list_char *tok)
{
	int			file_output;
	int			file_input;
	t_list_char	*tmp;

	tmp = tok;
	while (tmp)
	{
		file_input = get_infile_nb(tmp->cmd);
		file_output = get_outfile_nb(tmp->cmd);
		tmp->infiles = ft_calloc((file_input + file_output + 1), sizeof(char *));
		if (!tmp->infiles)
			return ;
		get_in_out_complet_list(tmp);
		tmp = tmp->next;
	}
}

void	get_good_fd(t_init *param, t_list_char *node)
{
	int	i;
	int	check;

	i = 0;
	check = 2;
	while (node->infiles[i])
	{
		if (ft_strlen(node->infiles[i]) == 2 && !ft_strcmp(node->infiles[i], ">>"))
		{
			get_out_fd(param, node, i);
			check = 0;
		}
		else if (!ft_strcmp(node->infiles[i], ">"))
		{
			get_out_fd(param, node, i);
			check = 0;
		}
		else if (ft_strlen(node->infiles[i]) == 2 && !ft_strcmp(node->infiles[i], "<<"))
		{
			get_in_fd(param, node, i);
			check = 1;
		}
		else if (!ft_strcmp(node->infiles[i], "<"))
		{
			get_in_fd(param, node, i);
			check = 1;
		}
		if (check == 0 && node->fd_outfile == -1)
			break ;
		if (check == 1 && node->fd_infile == -1)
			break ;
		i += 2;
	}
}

void	get_in_fd(t_init *param, t_list_char *node, int i)
{
	if (ft_strlen(node->infiles[i]) == 2 && !ft_strcmp(node->infiles[i], "<<"))
	{
		if (node->fd_infile != -1)
			close(node->fd_infile);
		node->fd_infile = open(node->heredoc->name, O_RDONLY);
	}
	else if (!ft_strcmp(node->infiles[i], "<"))
	{
		if (access(node->infiles[i + 1], F_OK | R_OK) != -1)
		{
			if (node->fd_infile != -1)
				close(node->fd_infile);
			node->fd_infile = open(node->infiles[i + 1], O_RDONLY, 0644);
		}
		else
		{
			if (node->fd_infile != -1)
				close(node->fd_infile);
			node->fd_infile = -1;
			param->status = 1;
			write (2, " No such file or directory", 26);
		}
	}
}

void	get_out_fd(t_init *param, t_list_char *node, int i)
{
	if (ft_strlen(node->infiles[i]) == 2 && !ft_strcmp(node->infiles[i], ">>"))
		check_access_app(node, i + 1);
	else if (!ft_strcmp(node->infiles[i], ">"))
		check_access_out(node, i + 1);
	if (node->fd_outfile == -1)
	{
		param->status= 1;
		write(2, " Permission denied", 18);
	}
}

void	check_access_out(t_list_char *node, int	i)
{
	if (access(node->infiles[i], F_OK | W_OK) != -1)
	{
		if (node->fd_outfile && node->fd_outfile != -1)
			close(node->fd_outfile);
		node->fd_outfile = open(node->infiles[i], O_WRONLY
				| O_TRUNC, 0644);
	}
	else if (access(node->infiles[i], F_OK) == -1) 
	{
		if (node->fd_outfile && node->fd_outfile != -1)
			close(node->fd_outfile);
		node->fd_outfile = open(node->infiles[i], O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		if (node->fd_outfile && node->fd_outfile != -1)
			close(node->fd_outfile);
		node->fd_outfile = -1;
	}
}

void	check_access_app(t_list_char *node, int	i)
{
	if (access(node->infiles[i], F_OK | W_OK) != -1)
	{
		if (node->fd_outfile && node->fd_outfile != -1)
			close(node->fd_outfile);
		node->fd_outfile = open(node->infiles[i], O_WRONLY
				| O_APPEND, 0644);
	}
	else if (access(node->infiles[i], F_OK) == -1)
	{
		if (node->fd_outfile && node->fd_outfile != -1)
			close(node->fd_outfile);
		node->fd_outfile = open(node->infiles[i], O_RDWR
			| O_CREAT | O_APPEND, 0644);
	}
	else
	{
		if (node->fd_outfile && node->fd_outfile != -1)
			close(node->fd_outfile);
		node->fd_outfile = -1;
	}
}
