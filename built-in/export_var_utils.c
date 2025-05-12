/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:22:16 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/12 17:03:45 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_add_value(t_env *tmp_exp, t_env *tmp_env,
	char *new_const, t_init *param)
{
	free(tmp_exp->cont);
	tmp_exp->cont = NULL;
	tmp_exp->cont = ft_strdup(new_const);
	if (param->create_x == 1)
	{
		free(tmp_env->cont);
		tmp_env->cont = NULL;
		tmp_env->cont = ft_strdup(new_const);
	}
	tmp_exp->exp = 0;
	free(new_const);
}

void	ft_alloc_new_const(t_list_char *tok, t_init *param,
	t_env *tmp_exp, t_env *tmp_env)
{
	int		j;
	char	*new_const;

	param->i_ex++;
	param->len_const_x = 0;
	new_const = NULL;
	j = param->i_ex;
	while (tok->cmd[1][param->i_ex])
	{
		param->len_const_x++;
		param->i_ex++;
	}
	new_const = ft_create_new_const(new_const, param, tmp_exp, tmp_env);
	if (new_const)
	{
		param->i_ex = 0;
		while (tok->cmd[1][j])
		{
			new_const[param->i_ex] = tok->cmd[1][j];
			param->i_ex++;
			j++;
		}
		ft_add_value(tmp_exp, tmp_env, new_const, param);
	}
}

void	ft_rest_var(t_env *tmp_env, t_env *tmp_exp,
	t_init *param, t_list_char *tok)
{
	tmp_env = param->lst_env;
	tmp_exp = param->lst_export;
	if (param->create_x == 2)
		ft_create_add_back(param, tok, tmp_exp, param->exist_x);
	else
		ft_add_export_only(param, tok, tmp_exp);
}

void	ft_init_var(t_init *param)
{
	param->i_ex = 1;
	param->create_x = 0;
	param->exist_x = 0;
}

int	ft_return_var(t_init *param, char *name)
{
	if (param->create_x != 2)
	{
		free(name);
		return (1);
	}
	return (0);
}
