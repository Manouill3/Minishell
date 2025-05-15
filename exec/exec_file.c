/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:21:52 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/15 10:57:58 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	add_redirection(t_list_char *node, int *i, int *j, char *red)
{
	if (!ft_strcmp(node->cmd[*i], red) && node->cmd[*i + 1])
	{
		node->infiles[(*j)++] = ft_strdup(node->cmd[(*i)++]);
		node->infiles[(*j)++] = ft_strdup(node->cmd[*i]);
	}
}

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
		add_redirection(node, &i, &j, "<");
		add_redirection(node, &i, &j, "<<");
		add_redirection(node, &i, &j, ">");
		add_redirection(node, &i, &j, ">>");
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
		tmp->infiles = ft_calloc((file_input + file_output + 1),
				sizeof(char *));
		if (!tmp->infiles)
			return ;
		get_in_out_complet_list(tmp);
		tmp = tmp->next;
	}
}

void	handle_redirection(t_init *param, t_list_char *node, int i, int *check)
{
	if (!ft_strcmp(node->infiles[i], ">") || !ft_strcmp(node->infiles[i], ">>"))
	{
		get_out_fd(param, node, i);
		*check = 0;
	}
	else if (!ft_strcmp(node->infiles[i], "<")
		|| !ft_strcmp(node->infiles[i], "<<"))
	{
		get_in_fd(param, node, i);
		*check = 1;
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
		handle_redirection(param, node, i, &check);
		if ((check == 0 && node->fd_outfile == -1)
			|| (check == 1 && node->fd_infile == -1))
			break ;
		i += 2;
	}
}
