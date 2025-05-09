/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:22:16 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/09 15:23:50 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	is_valid_identifier(t_list_char *tok, t_init *param)
{
	int	i;

	i = 1;
	while (tok->cmd[1][i] != '=' && tok->cmd[1][i])
	{
		if (!ft_isalnum(tok->cmd[1][i]))
		{
			param->status = 1;
			write(2, " not a valid identifier\n", 24);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_var_name(t_list_char *tok)
{
	int	i;

	i = 0;
	while (tok->cmd[1][i] && tok->cmd[1][i] != '=')
		i++;
	return (ft_substr(tok->cmd[1], 0, i));
}

int	should_create_var(t_env *env, t_list_char *tok, char *name)
{
	int	create;

	create = 0;
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (1);
		env = env->next;
	}
	if (ft_strchr(tok->cmd[1], '='))
		return (2);
	return (0);
}
