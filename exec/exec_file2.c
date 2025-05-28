/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:24:54 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/28 15:25:57 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	get_in_h(t_init *param, t_list_char *node, int i)
{
	int	status;

	if (!ft_strcmp(node->infiles[i], "<<"))
	{
		if (node->fd_infile != -1)
			close(node->fd_infile);
		if (g_exit_code != 130)
			node->fd_infile = open(node->heredoc->name, O_RDONLY, 0644);
		else if (!ft_strcmp(node->funct, "cat"))
		{
			status = param->status;
			close_all(param, node);
			ft_lstclear_mal(&param->mal);
			exit (status);
		}
	}
}

void	get_in_fd(t_init *param, t_list_char *node, int i)
{
	get_in_h(param, node, i);
	if (!ft_strcmp(node->infiles[i], "<"))
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
			write (2, "No such file or directory\n", 27);
		}
	}
}

void	get_out_fd(t_init *param, t_list_char *node, int i)
{
	if (!ft_strcmp(node->infiles[i], ">>"))
		check_access_app(node, i + 1);
	else if (!ft_strcmp(node->infiles[i], ">"))
		check_access_out(node, i + 1);
	if (node->fd_outfile == -1)
	{
		param->status = 1;
		write(2, "Permission denied\n", 19);
	}
}

void	check_access_out(t_list_char *node, int i)
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

void	check_access_app(t_list_char *node, int i)
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
