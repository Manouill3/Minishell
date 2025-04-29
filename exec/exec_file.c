/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:21:52 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/29 16:30:41 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	get_in_out_complet_list(t_list_char *node)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (node->cmd[i])
	{
		if (!ft_strcmp(node->cmd[i], "<"))
		{
			node->infiles[j++] = ft_strdup(node->cmd[i++]);
			node->infiles[j++] = ft_strdup(node->cmd[i]);
		}
		if (!ft_strcmp( node->cmd[i], ">"))
		{
			node->outfiles[k++] = ft_strdup(node->cmd[i++]);
			node->outfiles[k++] = ft_strdup(node->cmd[i]);
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
		tmp->infiles = ft_calloc((file_input + 1), sizeof(char *));
		tmp->outfiles = ft_calloc((file_output + 1), sizeof(char *));
		if (!tmp->infiles || !tmp->outfiles)
			return ;
		get_in_out_complet_list(tmp);
		tmp = tmp->next;
	}
}

void	get_in_fd(t_list_char *node)
{
	int	i;

	i = 0;
	while (node->infiles[i])
	{
		if (!ft_strcmp("<<", node->infiles[i]))
		{
			if (node->fd_infile != -1)
				close(node->fd_infile);
			node->fd_infile = open(node->heredoc->name, O_RDONLY);
		}
		else if (!ft_strcmp("<", node->infiles[i]) &&
				access(node->infiles[i + 1], F_OK | R_OK) != -1)
		{
			if (node->fd_infile != -1)
				close(node->fd_infile);
			node->fd_infile = open(node->infiles[i + 1], O_RDONLY, 0644);
		}
		i++;
	}
}

void	get_out_fd(t_list_char *node)
{
	int	i;

	i = 0;
	while (node->outfiles[i])
	{
		if (!ft_strcmp(">>", node->outfiles[i]))
			check_access_app(node, i + 1);
		else if (!ft_strcmp(">", node->outfiles[i]))
			check_access_out(node, i + 1);
		i++;
	}
}

void	check_access_out(t_list_char *node, int	i)
{
	if (access(node->outfiles[i], F_OK | W_OK) != -1)
	{
		if (node->fd_outfile && node->fd_outfile != -1)
			close(node->fd_outfile);
		node->fd_outfile = open(node->outfiles[i], O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		if (access(node->outfiles[i], F_OK) == -1)
		{
			if (node->fd_outfile && node->fd_outfile != -1)
				close(node->fd_outfile);
			node->fd_outfile = open(node->outfiles[i], O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		}
	}
}

void	check_access_app(t_list_char *node, int	i)
{
	if (access(node->outfiles[i], F_OK | W_OK) != -1)
	{
		if (node->fd_outfile && node->fd_outfile != -1)
			close(node->fd_outfile);
		node->fd_outfile = open(node->outfiles[i], O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	}
	else
	{
		if (access(node->outfiles[i], F_OK) == -1)
		{
			if (node->fd_outfile && node->fd_outfile != -1)
				close(node->fd_outfile);
			node->fd_outfile = open(node->outfiles[i], O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		}
	}
}
