/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:21:52 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/10 16:00:41 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	get_in_out_complet_list(t_list_char *tok, t_list_char *tmp,
			int file_output, int file_input)
{
	int	i;

	file_output = 0;
	file_input = 0;
	while (tmp)
	{
		i = -1;
		while (tmp->cmd[++i])
		{
			if (!ft_strcmp(tmp->cmd[i], "<"))
			{
				i++;
				tok->infiles[file_input] = ft_strdup(tmp->cmd[i]);
				file_input++;
			}
			else if (!ft_strcmp(tmp->cmd[i], ">")
				|| !ft_strcmp(tmp->cmd[i], ">>"))
			{
				i++;
				tok->outfiles[file_output] = ft_strdup(tmp->cmd[i]);
				file_output++;
			}
		}
		tmp = tmp->next;
	}
}

void	get_in_out(t_list_char *tok)
{
	int			i;
	int			file_output;
	int			file_input;
	t_list_char	*tmp;

	tmp = tok;
	file_output = 0;
	file_input = 0;
	while (tmp)
	{
		i = -1;
		while (tmp->cmd[++i])
		{
			if (!ft_strcmp(tmp->cmd[i], "<"))
				file_input++;
			else if (!ft_strcmp(tmp->cmd[i], ">")
				|| !ft_strcmp(tmp->cmd[i], ">>"))
				file_output++;
		}
		tmp = tmp->next;
	}
	tmp = tok;
	tok->infiles = ft_calloc((file_input + 1), sizeof(char *));
	tok->outfiles = ft_calloc((file_output + 1), sizeof(char *));
	get_in_out_complet_list(tok, tmp, file_output, file_input);
}

void	get_in_fd(t_list_char *node)
{
	int	i;

	i = 0;
	while (node->infiles[i])
	{
		if (access(node->outfiles[i], F_OK | R_OK) != -1)
		{
			if (node->fd_infile && node->fd_infile != -1)
				close(node->fd_infile);
			node->fd_infile = open(node->infiles[i], O_RDONLY, 0644);
		}
		else
			perror("infile");
		i++;
	}
}

void	get_out_fd(t_list_char *node)
{
	int	i;

	i = 0;
	while (node->outfiles[i])
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
		i++;
	}
}
