/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_red.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:24:06 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/27 13:25:41 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	add_redirection_in(t_list_char *node, int *i, int *j, t_mal *mal)
{
	if (!ft_strcmp(node->cmd[*i], "<<") && node->cmd[*i + 1])
	{
		node->infiles[(*j)++] = ft_strdup(node->cmd[(*i)++], mal);
		node->infiles[(*j)++] = ft_strdup(node->cmd[*i], mal);
	}
	if (!ft_strcmp(node->cmd[*i], "<") && node->cmd[*i + 1])
	{
		node->infiles[(*j)++] = ft_strdup(node->cmd[(*i)++], mal);
		node->infiles[(*j)++] = ft_strdup(node->cmd[*i], mal);
	}
}

void	add_redirection_out(t_list_char *node, int *i, int *j, t_mal *mal)
{
	if (!ft_strcmp(node->cmd[*i], ">>") && node->cmd[*i + 1])
	{
		node->infiles[(*j)++] = ft_strdup(node->cmd[(*i)++], mal);
		node->infiles[(*j)++] = ft_strdup(node->cmd[*i], mal);
	}
	if (!ft_strcmp(node->cmd[*i], ">") && node->cmd[*i + 1])
	{
		node->infiles[(*j)++] = ft_strdup(node->cmd[(*i)++], mal);
		node->infiles[(*j)++] = ft_strdup(node->cmd[*i], mal);
	}
}
