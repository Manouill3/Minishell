/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:06:32 by tcybak            #+#    #+#             */
/*   Updated: 2025/04/23 17:58:22 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_delete(t_env *tmp, char *name)
{
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			if (tmp->next != NULL)
				tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			ft_lstdelone_env(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

void    ft_unset(t_init *param, t_list_char *tok)
{
	int i;
	t_env *tmp;
	char    *name;

	i = 0;
	tmp = param->lst_env;
	while(tok->cmd[1][i])
	{
		if (ft_isalnum(tok->cmd[1][i]) == 0)
		{
			perror("export identifier");
			return ;
		}
		i++;
	}
	name = ft_substr(tok->cmd[1], 0, i);
	if (!name)
		return ;
	ft_delete(tmp, name);
	tmp = param->lst_export;
	ft_delete(tmp, name);
	free(name);
}
