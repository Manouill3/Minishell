/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:03 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/26 13:29:20 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	existing_vars(t_env *env, t_env *exp, char *name, char *add, t_mal *mal)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
		{
			env_content(env, add, mal);
			while (ft_strcmp(name, exp->name))
				exp = exp->next;
			if (!ft_strcmp(name, exp->name))
				export_content(exp, add, mal);
			// ft_free_env(add, name);
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
				ft_lstnew_env(ft_strdup(tok->cmd[1], param->mal), param->mal));
			while (env->next)
				env = env->next;
			get_name_env_more(env, param->mal);
			get_final_cont_more(env, param->mal);
			if (!add)
				exp->exp = 0;
			else
				export_content(exp, add, param->mal);
			// ft_free_env(add, name);
			return (1);
		}
		exp = exp->next;
	}
	return (0);
}

void	add_to_both_lists(t_init *param, t_list_char *tok)
{
	int		j;
	t_env	*env;
	t_env	*exp;

	j = tok->ex_j;
	ft_lstadd_back_env(&param->lst_env, ft_lstnew_env(ft_strdup(tok->cmd[j], param->mal), param->mal));
	ft_lstadd_back_env(&param->lst_export,
		ft_lstnew_env(ft_strdup(tok->cmd[j], param->mal), param->mal));
	env = param->lst_env;
	exp = param->lst_export;
	while (env->next)
		env = env->next;
	while (exp->next)
		exp = exp->next;
	get_name_env_more(env, param->mal);
	get_final_cont_more(env, param->mal);
	get_name_env_more(exp, param->mal);
	get_final_cont_more(exp, param->mal);
	// ft_free_env(add, name);
}

int	ft_add_value_var(t_init *param, int i, t_list_char *tok)
{
	int		j;
	int		len;
	char	*add;
	char	*name;

	j = tok->ex_j;
	len = ft_strlen(tok->cmd[j]) - i;
	add = ft_substr(tok->cmd[j], i, len, param->mal);
	name = ft_substr(tok->cmd[j], 0, (i - 2), param->mal);
	if (existing_vars(param->lst_env, param->lst_export, name, add, param->mal) == 1)
		return (0);
	if (add_to_env(param, name, add, tok) == 1)
		return (0);
	add_to_both_lists(param, tok);
	return (0);
}
