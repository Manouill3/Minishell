/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:23:09 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/09 15:23:45 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	assign_const_to_envs(t_env *exp, t_env *env, char *new_const, int create)
{
	free(exp->cont);
	exp->cont = ft_strdup(new_const);
	if (create == 1 && env)
	{
		free(env->cont);
		env->cont = ft_strdup(new_const);
	}
	exp->exp = 0;
	free(new_const);
}

char	*extract_const_part(t_list_char *tok, int *start)
{
	int		i;
	int		len;
	char	*res;

	*start += 1;
	i = *start;
	len = 0;
	while (tok->cmd[1][i])
	{
		len++;
		i++;
	}
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (tok->cmd[1][*start])
		res[i++] = tok->cmd[1][(*start)++];
	res[i] = '\0';
	return (res);
}

int	handle_export_conditions(t_env *exp, t_list_char *tok, char *name, int *create, t_env *env)
{
	int		i;
	int		j;
	char	*new_const;
	int		exist;

	i = 0;
	exist = 0;
	while (tok->cmd[1][i] && tok->cmd[1][i] != '=')
		i++;
	while (exp)
	{
		if (!ft_strcmp(exp->name, name))
		{
			exist = 1;
			if (*create == 1 && tok->cmd[1][i] != '=')
				exp->exp = 0;
			if (tok->cmd[1][i] != '=' && *create != 2)
				return (exist);
			if (tok->cmd[1][i] == '=')
			{
				j = i;
				new_const = extract_const_part(tok, &i);
				if (new_const)
					assign_const_to_envs(exp, env, new_const, *create);
				if (*create != 2)
					return (exist);
			}
		}
		exp = exp->next;
	}
	return (exist);
}
