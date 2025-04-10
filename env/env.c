/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:01:32 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 20:01:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	get_final_cont(t_env *env)
{
	int		i;
	char	*tmp_cont;
	t_env	*tmp;

	tmp = env;;
	while (tmp)
	{
		i = 0;
		while (tmp->name[i])
			i++;
		i++;
		tmp_cont = tmp->cont;
		tmp->cont = ft_substr(tmp->cont, i, ft_strlen(tmp->cont) - 1);
		free(tmp_cont);
		tmp = tmp->next;
	}
}

void	get_name_env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		curr->name = ft_substr(curr->cont, 0,
				ft_strchr(curr->cont, '=') - curr->cont);
		curr = curr->next;
	}
}

int	get_env(t_init *param, char **env)
{
	int	i;

	i = 0;
	param->lst_env = NULL;
	while (env[i])
	{
		ft_lstadd_back_env(&param->lst_env, ft_lstnew_env(ft_strdup(env[i])));
		i++;
	}
	if (param->lst_env == NULL)
		return (1);
	get_name_env(param->lst_env);
	get_final_cont(param->lst_env);
	return (0);
}
