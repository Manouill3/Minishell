/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:21:52 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/10 14:27:33 by mdegache         ###   ########.fr       */
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

void	check_access_output(t_list_char *tok)
{
	int	i;
	int	fd_outfile;

	i = 0;
	fd_outfile = -1;
	if (tok->outfiles)
	{
		while (tok->outfiles[i])
		{
			if (access(tok->outfiles[i], F_OK | W_OK) != -1)
			{
				if (fd_outfile != -1)
					close(fd_outfile);
				fd_outfile = open(tok->outfiles[i], O_WRONLY
						| O_CREAT | O_TRUNC, 0644);
			}
			else
			{
				if (access(tok->outfiles[i], F_OK) == -1)
				{
					if (fd_outfile != -1)
						close(fd_outfile);
					fd_outfile = open(tok->outfiles[i], O_WRONLY
							| O_CREAT | O_TRUNC, 0644);
				}
			}
			i++;
		}
	}
	if (fd_outfile != -1)
	{
		close(tok->fd_outfile);
		tok->fd_outfile = fd_outfile;
	}
	// if (tok->fd_outfile == -1)
	// 	tok->fd_outfile = open("/dev/tty", O_WRONLY);
}

void	check_access_input(t_list_char *tok)
{
	int	i;
	int	fd_infile;
	
	i = 0;
	fd_infile = -1;
	if (tok->infiles)
	{
		while (tok->infiles[i])
		{
			if (access(tok->infiles[i], R_OK | F_OK) != -1)
			{
				if (fd_infile != -1)
					close(fd_infile);
				fd_infile = open(tok->infiles[i], O_RDONLY, 0644);
			}
			else
				perror("infile");
			i++;
		}
	}
	if (fd_infile != -1)
	{
		close(tok->fd_infile);
		tok->fd_infile = fd_infile;
	}
	// if (tok->fd_infile == -1)
	// 	tok->fd_infile = open("/dev/tty", O_RDONLY);
}
