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

	i = 0;
	while (i < param->i_ex)
	{
		while (i < len_tmp)
		{
			tmp_cmd[i] = tmp_val[i];
			i++;
		}
		i++;
	}
}

void	ft_count_len(int *len_tmp, char **tmp_val)
{
	while (tmp_val[(*len_tmp)])
		(*len_tmp)++;
}

char	**ft_create_tmp_cmd(char **tmp_cmd, int i, int len_tmp, t_mal *mal)
{
	tmp_cmd = add_calloc(mal, (i + len_tmp + 1), (sizeof(char *)));
	if (!tmp_cmd)
		return (NULL);
	return (tmp_cmd);
}

void	exec_verif_exp(t_init *param, t_list_char *tmp)
{
	int			i;
	int			len_tmp;
	char		**tmp_val;
	char		**tmp_cmd;

	i = 0;
	tmp_cmd = NULL;
	if (tmp->cmd[i] && tmp->len_ind_exp >= 1
		&& ft_strcmp(tmp->funct, tmp->cmd[i])
		&& white_or_not(tmp->cmd[i]) && tmp->ind_exp[i] == i)
	{
		tmp_cmd = ft_all_one_ligne(param, tmp_cmd, tmp);
		tmp_val = ft_exp_split_par(tmp_cmd[0], param->mal);
		while (tmp_val && tmp_val[i])
			i++;
		len_tmp = 0;
		ft_count_len(&len_tmp, tmp_val);
		tmp_cmd = ft_create_tmp_cmd(tmp_cmd, i, len_tmp, param->mal);
		param->i_ex = i + len_tmp;
		end_verif_exp(param, tmp_cmd, tmp_val, len_tmp);
		ft_free_realoc(param, tmp, tmp_cmd);
	}
	exec_verif_exp2(param, tmp, i);
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
