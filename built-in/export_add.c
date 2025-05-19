/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:03 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/19 13:47:40 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	existing_vars(t_env *env, t_env *exp, char *name, char *add)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
		{
			env_content(env, add);
			while (ft_strcmp(name, exp->name))
				exp = exp->next;
			if (!ft_strcmp(name, exp->name))
				export_content(exp, add);
			ft_free_env(add, name);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	add_to_env(t_init *param, char *name, char *add, t_list_char *tok)
{
	t_env	*env;
	t_env	*exp;

	env = param->lst_env;
	exp = param->lst_export;
	while (exp)
	{
		if (!ft_strcmp(name, exp->name))
		{
			ft_lstadd_back_env(&param->lst_env,
				ft_lstnew_env(ft_strdup(tok->cmd[1])));
			while (env->next)
				env = env->next;
			get_name_env_more(env);
			get_final_cont_more(env);
			if (!add)
				exp->exp = 0;
			else
				export_content(exp, add);
			ft_free_env(add, name);
			return (1);
		}
		exp = exp->next;
	}
	return (0);
}

void	add_to_both_lists(t_init *param, t_list_char *tok,
		char *add, char *name)
{
	t_env	*env;
	t_env	*exp;

	ft_lstadd_back_env(&param->lst_env, ft_lstnew_env(ft_strdup(tok->cmd[1])));
	ft_lstadd_back_env(&param->lst_export,
		ft_lstnew_env(ft_strdup(tok->cmd[1])));
	env = param->lst_env;
	exp = param->lst_export;
	while (env->next)
		env = env->next;
	while (exp->next)
		exp = exp->next;
	get_name_env_more(env);
	get_final_cont_more(env);
	get_name_env_more(exp);
	get_final_cont_more(exp);
	ft_free_env(add, name);
}

int	ft_add_value_var(t_init *param, int i, t_list_char *tok)
{
	int		len;
	char	*add;
	char	*name;

	len = ft_strlen(tok->cmd[1]) - i;
	add = ft_substr(tok->cmd[1], i, len);
	name = ft_substr(tok->cmd[1], 0, (i - 2));
	if (existing_vars(param->lst_env, param->lst_export, name, add) == 1)
		return (0);
	if (add_to_env(param, name, add, tok) == 1)
		return (0);
	add_to_both_lists(param, tok, add, name);
	return (0);
}
