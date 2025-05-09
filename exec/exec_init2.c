/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:14:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/09 11:15:28 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	no_red_len(char **tab, t_list_char *tmp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < tmp->len_cmd)
	{
		if (ft_strlen(tab[i]) < 1)
		{
			i++;
			continue ;
		}
		if (tab[i] && ft_strcmp(tab[i], ">") && ft_strcmp(tab[i], "<"))
			len++;
		else
			i++;
		i++;
	}
	return (len);
}

void	no_red_ann(int i, int j, int len, t_list_char *tmp)
{
	while (j < len && i < tmp->len_cmd)
	{
		if (ft_strlen(tmp->cmd[i]) < 1)
		{
			i++;
			continue ;
		}
		if (ft_strcmp(">", tmp->cmd[i]) && ft_strcmp("<", tmp->cmd[i])
			&& ft_strcmp(">>", tmp->cmd[i]) && ft_strcmp("<<", tmp->cmd[i]))
			tmp->no_red[j++] = ft_strdup(tmp->cmd[i]);
		else
			i++;
		i++;
	}
}

void	get_no_red(t_list_char *tok)
{
	t_list_char	*tmp;
	int			len;
	int			i;
	int			j;

	tmp = tok;
	while (tmp)
	{
		i = 0;
		j = 0;
		len = no_red_len(tmp->cmd, tmp);
		tmp->no_red = ft_calloc(len + 1, sizeof(char *));
		if (!tok->no_red)
			return ;
		no_red_ann(i, j, len, tmp);
		tmp = tmp->next;
	}
}
