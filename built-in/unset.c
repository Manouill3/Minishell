/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:06:32 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/20 10:48:41 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_delete(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				env = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			ft_lstdelone_env(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

int	ft_error_unset(t_init *param, t_list_char *tok, int *j, int i)
{
	if (ft_isalnum(tok->cmd[i][(*j)]) == 0)
	{
		param->status = 1;
		perror("unset");
		return (1);
	}
	(*j)++;
	return (0);
}

void	ft_unset(t_init *param, t_list_char *tok)
{
	int		i;
	int		j;
	t_env	*tmp;
	char	*name;

	tmp = param->lst_env;
	i = 0;
	while (tok->cmd[i])
	{
		j = 0;
		while (tok->cmd[i][j])
			if (ft_error_unset(param, tok, &j, i) == 1)
				return ;
		name = ft_substr(tok->cmd[i], 0, j);
		if (!name)
			return ;
		tmp = param->lst_env;
		ft_delete(tmp, name);
		tmp = param->lst_export;
		ft_delete(tmp, name);
		free(name);
		param->status = 0;
		i++;
	}
}
