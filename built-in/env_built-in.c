/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built-in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:32:09 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/28 16:08:09 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_error_env(t_init *param, t_list_char *tmp_tok, int i)
{
	if (tmp_tok->ind_exp[0] == i)
	{
		param->status = 126;
		write(2, "Permission denied\n", 18);
	}
	else
	{
		param->status = 127;
		write(2, "No such file or directory\n", 26);
	}
}

void	ft_env(t_init *param, t_env *env)
{
	int			i;
	t_list_char	*tmp_tok;
	t_env		*tmp;

	i = 1;
	tmp = env;
	tmp_tok = param->tok;
	while (tmp_tok->cmd[i])
	{
		if (ft_strlen(tmp_tok->cmd[i]) != 0)
		{
			ft_error_env(param, tmp_tok, i);
			return ;
		}
		i++;
	}
	while (tmp)
	{
		printf("%s=", tmp->name);
		printf("%s\n", tmp->cont);
		tmp = tmp->next;
	}
}
