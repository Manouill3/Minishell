/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:22:16 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/29 21:56:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_add_value(t_env *tmp_exp, t_env *tmp_env,
	char *new_const, t_init *param)
{
	tmp_exp->cont = NULL;
	tmp_exp->cont = ft_strdup(new_const, param->mal);
	if (param->create_x == 1)
	{
		tmp_env->cont = NULL;
		tmp_env->cont = ft_strdup(new_const, param->mal);
	}
	tmp_exp->exp = 0;
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
	while (tok->cmd[tok->ex_j][param->i_ex])
	{
		param->len_const_x++;
		param->i_ex++;
	}
	new_const = ft_create_new_const(new_const, param, tmp_exp, tmp_env);
	if (new_const)
	{
		param->i_ex = 0;
		while (tok->cmd[tok->ex_j][j])
		{
			new_const[param->i_ex] = tok->cmd[tok->ex_j][j];
			param->i_ex++;
			j++;
		}
		ft_add_value(tmp_exp, tmp_env, new_const, param);
	}
}

void	ft_rest_var(t_env *tmp_exp,
	t_init *param, t_list_char *tok)
{
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

int	ft_return_var(t_init *param)
{
	if (param->create_x != 2)
		return (1);
	return (0);
}
