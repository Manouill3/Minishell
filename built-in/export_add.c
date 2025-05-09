/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:03 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/09 15:54:12 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	env_content(t_env *env, char *add)
{
	char *tmp;

	tmp = ft_strjoin(env->cont, add);
	free(env->cont);
	env->cont = tmp;
}

void	export_content(t_env *exp, char *add)
{
	char *tmp;

	tmp = ft_strjoin(exp->cont, add);
	free(exp->cont);
	exp->cont = tmp;
}

int existing_vars(t_env *env, t_env *exp, char *name, char *add)
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
			free(add);
			free(name);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	add_to_env_if_in_export(t_init *param, char *name, char *add, t_list_char *tok)
{
	t_env *env = param->lst_env;
	t_env *exp = param->lst_export;

	while (exp)
	{
		if (!ft_strcmp(name, exp->name))
		{
			ft_lstadd_back_env(&param->lst_env, ft_lstnew_env(ft_strdup(tok->cmd[1])));
			while (env->next)
				env = env->next;
			get_name_env_more(env);
			get_final_cont_more(env);
			if (!add)
				exp->exp = 0;
			else
				export_content(exp, add);
			free(add);
			free(name);
			return (1);
		}
		exp = exp->next;
	}
	return (0);
}

void	add_to_both_lists(t_init *param, t_list_char *tok, char *add, char *name)
{
	t_env *env;
	t_env *exp;

	ft_lstadd_back_env(&param->lst_env, ft_lstnew_env(ft_strdup(tok->cmd[1])));
	ft_lstadd_back_env(&param->lst_export, ft_lstnew_env(ft_strdup(tok->cmd[1])));
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
	free(add);
	free(name);
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
	if (add_to_env_if_in_export(param, name, add, tok) == 1)
		return (0);
	add_to_both_lists(param, tok, add, name);
	return (0);
}

// int		ft_add_value_var(t_init *param, int i, t_list_char *tok)
// {
// 	int	    len;
// 	char	*add;
// 	char	*name;
// 	char	*tmp;
// 	t_env 	*tmp_env;
// 	t_env	*tmp_exp;

// 	tmp_env = param->lst_env;
// 	tmp_exp = param->lst_export;
// 	tmp = NULL;
// 	len = ft_strlen(tok->cmd[1]) - i;
// 	add = ft_substr(tok->cmd[1], i, len);
// 	name = ft_substr(tok->cmd[1], 0, (i - 2));
// 	while (tmp_env)
// 	{
// 		if (!ft_strcmp(name, tmp_env->name))
// 		{
// 			tmp = ft_strjoin(tmp_env->cont, add);
// 			free(tmp_env->cont);
// 			tmp_env->cont = NULL;
// 			tmp_env->cont = tmp;
// 			while(ft_strcmp(name, tmp_exp->name))
// 				tmp_exp = tmp_exp->next;
// 			if (!ft_strcmp(name, tmp_exp->name))
// 			{
// 				tmp = ft_strjoin(tmp_exp->cont, add);
// 				free(tmp_exp->cont);
// 				tmp_exp->cont = NULL;
// 				tmp_exp->cont = tmp;
// 			}
// 			free(add);
// 			free(name);
// 			return (0);
// 		}
// 		tmp_env = tmp_env->next;
// 	}
// 	tmp_env = param->lst_env;
// 	while (tmp_exp)
// 	{
// 			if (!ft_strcmp(name, tmp_exp->name))
// 			{
// 				ft_lstadd_back_env(&param->lst_env, ft_lstnew_env(ft_strdup(tok->cmd[1])));
// 				while (tmp_env->next != NULL)
// 					tmp_env = tmp_env->next;
// 				get_name_env_more(tmp_env);
// 				get_final_cont_more(tmp_env);
// 				if (!add)
// 					tmp_exp->exp = 0;
// 				else
// 				{
// 					tmp = ft_strjoin(tmp_exp->cont, add);
// 					free(tmp_exp->cont);
// 					tmp_exp->cont = NULL;
// 					tmp_exp->cont = tmp;
// 				}
// 				free(add);
// 				free(name);
// 				return (0);
// 			}
// 		tmp_exp = tmp_exp->next;
// 	}
// 	tmp_env = NULL;
// 	tmp_exp = NULL;
// 	tmp_env = param->lst_env;
// 	tmp_exp = param->lst_export;
// 	ft_lstadd_back_env(&param->lst_env, ft_lstnew_env(ft_strdup(tok->cmd[1])));
// 	ft_lstadd_back_env(&param->lst_export, ft_lstnew_env(ft_strdup(tok->cmd[1])));
// 	while (tmp_exp->next != NULL)
// 		tmp_exp = tmp_exp->next;
// 	while (tmp_env->next != NULL)
// 		tmp_env = tmp_env->next;
// 	get_name_env_more(tmp_env);
// 	get_final_cont_more(tmp_env);
// 	get_name_env_more(tmp_exp);
// 	get_final_cont_more(tmp_exp);
// 	free(add);
// 	free(name);
// 	return (0);
// }