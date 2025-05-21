/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:20:20 by marvin            #+#    #+#             */
/*   Updated: 2025/05/13 19:20:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	end_verif_exp(t_init *param, char **tmp_cmd,
		char **tmp_val, int len_tmp)
{
	int			i;
	int			j;
	t_list_char	*tmp;

	i = 0;
	j = 0;
	tmp = param->tok;
	while (i < param->i_ex)
	{
		while (i < len_tmp)
		{
			tmp_cmd[i] = tmp_val[i];
			i++;
		}
		while (i < param->i_ex)
		{
			tmp_cmd[i] = tmp->cmd[j + 1];
			i++;
			j++;
		}
	}
}

void	ft_count_len(int *len_tmp, int *i, char **tmp_val, t_list_char *tmp)
{
	while (tmp_val[(*len_tmp)])
		(*len_tmp)++;
	while (tmp->cmd[(*i) + 1])
		(*i)++;
}

char	**ft_create_tmp_cmd(char **tmp_cmd, int i, int len_tmp, char **tmp_val)
{
	tmp_cmd = ft_calloc((i + len_tmp + 1), (sizeof(char *)));
	if (!tmp_cmd)
	{
		free(tmp_val);
		return (NULL);
	}
	return (tmp_cmd);
}

void	exec_verif_exp(t_init *param, t_list_char *tmp)
{
	int			i;
	int			len_tmp;
	char		**tmp_val;
	char		**tmp_cmd;

	i = 0;
	while (i < tmp->len_ind_exp)
	{
		if (tmp->cmd[i] && ft_strcmp(tmp->funct, tmp->cmd[i])
			&& white_or_not(tmp->cmd[i]) && tmp->ind_exp[i] == i)
		{
			tmp_val = ft_exp_split(tmp->cmd[i]);
			free(tmp->cmd[i]);
			tmp->cmd[i] = NULL;
			len_tmp = 0;
			ft_count_len(&len_tmp, &i, tmp_val, tmp);
			tmp_cmd = ft_create_tmp_cmd(tmp_cmd, i, len_tmp, tmp_val);
			param->i_ex = i + len_tmp;
			end_verif_exp(param, tmp_cmd, tmp_val, len_tmp);
			ft_free_realoc(param, tmp, tmp_cmd, tmp_val);
		}
		i++;
	}
}

void	verif_expand(t_init *param)
{
	t_list_char	*tmp;

	if (param->tok)
	{
		tmp = param->tok;
		exec_verif_exp(param, tmp);
	}
}
