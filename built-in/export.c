/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:14:17 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/28 12:58:09 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_add_export_only(t_init *param, t_list_char *tok, t_env *tmp_exp)
{
	int	j;

	j = tok->ex_j;
	ft_lstadd_back_env(&param->lst_export,
		ft_lstnew_env(ft_strdup(tok->cmd[j], param->mal), param->mal));
	while (tmp_exp->next != NULL)
		tmp_exp = tmp_exp->next;
	get_name_env(tmp_exp, param->mal);
	get_final_cont(tmp_exp, param->mal);
	tmp_exp->exp = 1;
	return ;
}

int	ft_continue_value(t_init *param, t_list_char *tok)
{
	int	i;
	int	j;

	i = 1;
	j = tok->ex_j;
	while ((tok->cmd[j][i] != '=' && tok->cmd[j][i]))
	{
		if (tok->cmd[j][i] == '+' && tok->cmd[j][i + 1] == '=')
		{
			i = i + 2;
			ft_add_value_var(param, i, tok);
			return (0);
		}
		if (ft_isalnum(tok->cmd[j][i]) == 0 && tok->cmd[j][i] != '_')
		{
			param->status = 1;
			write(2, "not a valid identifier1\n", 24);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_create_add_back(t_init *param, t_list_char *tok,
		t_env *tmp_exp, int exist)
{
	int		j;
	t_env	*tmp_env;

	j = tok->ex_j;
	tmp_env = param->lst_env;
	if (exist != 1)
	{
		ft_lstadd_back_env(&param->lst_export,
			ft_lstnew_env(ft_strdup(tok->cmd[j], param->mal), param->mal));
		while (tmp_exp->next != NULL)
			tmp_exp = tmp_exp->next;
		get_name_env(tmp_exp, param->mal);
		get_final_cont(tmp_exp, param->mal);
	}
	ft_lstadd_back_env(&param->lst_env,
		ft_lstnew_env(ft_strdup(tok->cmd[j], param->mal), param->mal));
	while (tmp_env->next != NULL)
		tmp_env = tmp_env->next;
	get_name_env(tmp_env, param->mal);
	get_final_cont(tmp_env, param->mal);
}

void	ft_print_exp(t_env *tmp_exp)
{
	while (tmp_exp)
	{
		printf("declare -x ");
		if (tmp_exp->cont[0] == '\0' && tmp_exp->exp == 1)
			printf("%s\n", tmp_exp->name);
		else
		{
			printf("%s=", tmp_exp->name);
			printf("\"%s\"\n", tmp_exp->cont);
		}
		tmp_exp = tmp_exp->next;
	}
}

void	ft_export(t_init *param, t_list_char *tok)
{
	int		verif;
	t_env	*tmp_exp;

	verif = 0;
	tmp_exp = param->lst_export;
	if (tok->cmd[1] == NULL)
		ft_print_exp(tmp_exp);
	tok->ex_j = 1;
	while (tok->ex_j < tok->len_cmd && tok->ex_j)
	{
		if (ft_isalpha(tok->cmd[tok->ex_j][0]) || tok->cmd[tok->ex_j][0] == '_')
		{
			verif = ft_continue_value(param, tok);
			if (verif == 1)
				ft_create_var(param, tok, tmp_exp);
		}
		else
		{
			param->status = 1;
			write(2, "not a valid identifier2\n", 24);
			break ;
		}
		tok->ex_j++;
	}
}
