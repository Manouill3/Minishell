/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:05:45 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/10 11:07:29 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static char	*ft_var_tmp(t_list_char *tmp, int i)
{
	int		j;
	char	*tmp_var_env;

	j = 0;
	i++;
	tmp_var_env = ft_calloc(ft_strlen(&tmp->data[i]) + 1, sizeof(char));
	if (!tmp_var_env)
		return (NULL);
	while(tmp->data[i] && tmp->data[i] != '"')
	{
		tmp_var_env[j] = tmp->data[i];
		j++;
		i++;
	}
	return (tmp_var_env);
}

void    ft_expand(t_list_char *lst, t_list_char *env)
{
	int			i;
	char		*var_tmp;
	t_list_char *tmp;
	t_list_char	*tmp_env;

	tmp = lst;
	tmp_env = env;
	var_tmp = NULL;
	while(tmp)
	{
		i = 0;
		if (tmp->data[0] != 39)
		{
			while(tmp->data[i])
			{
				if (tmp->data[i] == '$')
				{
					var_tmp = ft_var_tmp(tmp, i);
					while(tmp_env)
					{
						if (!ft_strcmp(var_tmp, tmp_env->data))
							break ;
						tmp_env = tmp_env->next;
					}
					free(var_tmp);
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
}
