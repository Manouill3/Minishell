/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:23:09 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/27 10:43:19 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	ft_verif_exp(t_init *param, t_list_char *tok)
{
	int	j;

	j = tok->ex_j;
	while (tok->cmd[j][param->i_ex] != '=' && tok->cmd[j][param->i_ex])
	{
		if (ft_isalnum(tok->cmd[j][param->i_ex]) == 0)
		{
			param->status = 1;
			write(2, "not a valid identifier\n", 24);
			return (1);
		}
		param->i_ex++;
	}
	return (0);
}

t_env	*ft_verif_env_create(t_env *tmp_env, char *name, t_init *param)
{
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->name, name))
		{
			param->create_x = 1;
			break ;
		}
		tmp_env = tmp_env->next;
	}
	return (tmp_env);
}

int	ft_existing_export(char	*name, t_env *tmp_exp,
		t_init *param, t_list_char *tok)
{
	int	j;

	j = tok->ex_j;
	if (!ft_strcmp(tmp_exp->name, name))
		param->exist_x = 1;
	if (!ft_strcmp(tmp_exp->name, name) && param->create_x == 1
		&& tok->cmd[j][param->i_ex] != '=')
	{
		tmp_exp->exp = 0;
		if (param->create_x != 2)
		{
			// free(name);
			return (1);
		}
	}
	if (!ft_strcmp(tmp_exp->name, name) && tok->cmd[j][param->i_ex] != '=')
	{
		tmp_exp->exp = 1;
		if (param->create_x != 2)
		{
			// free(name);
			return (1);
		}
	}
	return (0);
}

char	*ft_create_new_const(char *new_const, t_init *param,
		t_env *tmp_exp, t_env *tmp_env)
{
	new_const = add_calloc(param->mal, param->len_const_x + 1, sizeof(char));
	if (!new_const)
	{
		new_const = NULL;
		tmp_exp->cont = NULL;
		if (param->create_x == 1)
			tmp_env->cont = NULL;
	}
	return (new_const);
}

void	ft_create_var(t_init *param, t_list_char *tok, t_env *tmp_exp)
{
	char	*name;
	t_env	*tmp_env;

	ft_init_var(param);
	tmp_env = param->lst_env;
	if (ft_verif_exp(param, tok) == 1)
		return ;
	name = ft_substr(tok->cmd[tok->ex_j], 0, (param->i_ex), param->mal);
	tmp_env = ft_verif_env_create(tmp_env, name, param);
	if (param->create_x == 0 && tok->cmd[tok->ex_j][param->i_ex] == '=')
		param->create_x = 2;
	while (tmp_exp)
	{
		if (ft_existing_export(name, tmp_exp, param, tok) == 1)
			return ;
		if (!ft_strcmp(tmp_exp->name, name) && tok->cmd[tok->ex_j][param->i_ex] == '=')
		{
			ft_alloc_new_const(tok, param, tmp_exp, tmp_env);
			if (ft_return_var(param) == 1)
				return ;
		}
		tmp_exp = tmp_exp->next;
	}
	ft_rest_var(tmp_env, tmp_exp, param, tok);
	// free(name);
}
