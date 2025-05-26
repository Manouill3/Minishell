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

void	get_final_cont(t_env *env, t_mal *mal)
{
	int		i;
	// char	*tmp_cont;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		i = 0;
		while (tmp->name[i])
			i++;
		i++;
		// tmp_cont = tmp->cont;
		tmp->cont = ft_substr(tmp->cont, i, ft_strlen(tmp->cont) - 1, mal);
		// free(tmp_cont);
		tmp = tmp->next;
	}
}

void	get_name_env(t_env *env, t_mal *mal)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		curr->name = ft_substr(curr->cont, 0,
				ft_strchr(curr->cont, '=') - curr->cont, mal);
		curr = curr->next;
	}
}

void	get_name_env_more(t_env *env, t_mal *mal)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		curr->name = ft_substr(curr->cont, 0,
				ft_strchr(curr->cont, '+') - curr->cont, mal);
		curr = curr->next;
	}
}

void	get_final_cont_more(t_env *env, t_mal *mal)
{
	int		i;
	// char	*tmp_cont;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		i = 0;
		while (tmp->name[i])
			i++;
		i = i + 2;
		// tmp_cont = tmp->cont;
		tmp->cont = ft_substr(tmp->cont, i, ft_strlen(tmp->cont) - 1, mal);
		// free(tmp_cont);
		tmp = tmp->next;
	}
}

int	get_env(t_init *param, char **env)
{
	int	i;

	i = 0;
	param->lst_env = NULL;
	param->lst_export = NULL;
	while (env[i])
	{
		ft_lstadd_back_env(&param->lst_env,
			ft_lstnew_env(ft_strdup(env[i], param->mal), param->mal));
		ft_lstadd_back_env(&param->lst_export,
			ft_lstnew_env(ft_strdup(env[i], param->mal), param->mal));
		i++;
	}
	if (param->lst_env == NULL)
		return (1);
	get_name_env(param->lst_env, param->mal);
	get_name_env(param->lst_export, param->mal);
	get_final_cont(param->lst_env, param->mal);
	get_final_cont(param->lst_export, param->mal);
	return (0);
}
