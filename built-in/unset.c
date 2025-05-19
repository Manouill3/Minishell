/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:06:32 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/19 10:32:44 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

// void	ft_delete(t_env *tmp, char *name)
// {
// 	while (tmp)
// 	{
// 		printf("name = %s, tmp->name = %s\n", name, tmp->name);
// 		if (!ft_strcmp(name, tmp->name))
// 		{
// 			if (tmp->next != NULL)
// 				tmp->prev->next = tmp->next;
// 			tmp->next->prev = tmp->prev;
// 			ft_lstdelone_env(tmp);
// 			return ;
// 		}
// 		tmp = tmp->next;
// 	}
// }

void	ft_delete(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				*env = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			ft_lstdelone_env(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

// void	ft_unset(t_init *param, t_list_char *tok)
// {
// 	int		i;
// 	t_env	*tmp;
// 	char	*name;

// 	i = 0;
// 	tmp = param->lst_env;
// 	while (tok->cmd[1] && tok->cmd[1][i])
// 	{
// 		if (ft_isalnum(tok->cmd[1][i]) == 0)
// 		{
// 			param->status = 1;
// 			perror("unset");
// 			return ;
// 		}
// 		i++;
// 	}
// 	name = ft_substr(tok->cmd[1], 0, i);
// 	if (!name)
// 		return ;
// 	tmp = param->lst_env;
// 	ft_delete(&tmp, name);
// 	tmp = param->lst_export;
// 	ft_delete(&tmp, name);
// 	free(name);
// 	param->status = 0;
// }

void	ft_unset(t_init *param, t_list_char *tok)
{
	int		i;
	int	j;
	t_env	*tmp;
	char	*name;

	tmp = param->lst_env;
	i = 0;
	while (tok->cmd[i])
	{
		j = 0;
		while (tok->cmd[i][j])
		{
			if (ft_isalnum(tok->cmd[i][j]) == 0)
			{
				param->status = 1;
				perror("unset");
				return ;
			}
			j++;
		}
		name = ft_substr(tok->cmd[i], 0, j);
		if (!name)
			return ;
		tmp = param->lst_env;
		ft_delete(&tmp, name);
		tmp = param->lst_export;
		ft_delete(&tmp, name);
		free(name);
		param->status = 0;
		i++;
	}
}
