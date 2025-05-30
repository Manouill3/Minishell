/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:39:28 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/30 08:44:39 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	**ft_all_one_ligne(t_init *param, char **tmp_cmd, t_list_char *tmp)
{
	int	x;
	int	y;
	int	len;

	x = -1;
	len = 0;
	free_tab(tmp_cmd);
	tmp_cmd = ft_create_calloc_exp(param, tmp_cmd, tmp);
	while (tmp->cmd && tmp->cmd[++x])
	{
		y = 0;
		while (tmp->cmd && tmp->cmd[x][y])
		{
			if (tmp->cmd[x][y] == '<' || tmp->cmd[x][y] == '>')
			{
				tmp_cmd[0][len++] = '"';
				tmp_cmd[0][len++] = tmp->cmd[x][y++];
				tmp_cmd[0][len++] = '"';
			}
			else
				tmp_cmd[0][len++] = tmp->cmd[x][y++];
		}
		tmp_cmd[0][len++] = ' ';
	}
	return (tmp_cmd);
}

char	**ft_create_calloc_exp(t_init *param, char **tmp_cmd, t_list_char *tmp)
{
	int	x;
	int	y;
	int	len;

	x = -1;
	len = 0;
	while (tmp->cmd[++x])
	{
		y = 0;
		while (tmp->cmd[x][y])
		{
			if (tmp->cmd[x][y] == '<' || tmp->cmd[x][y] == '>')
				len += 2;
			y++;
			len++;
		}
		len++;
	}
	tmp_cmd = add_calloc(param->mal, sizeof(char *), 2);
	if (!tmp_cmd)
		return (NULL);
	tmp_cmd[0] = add_calloc(param->mal, sizeof(char), (len + 1));
	if (!tmp_cmd[0])
		return (NULL);
	return (tmp_cmd);
}

int	ft_verif_expand_good(t_list_char *tmp)
{
	int	i;
	int	j;

	i = 0;
	while (tmp->cmd[i])
	{
		j = 0;
		while (tmp->cmd[i][j])
		{
			if (tmp->cmd[i][j] == '$' || tmp->cmd[i][j] == '=')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	exec_verif_exp2(t_init *param, t_list_char *tmp, int i)
{
	int			len_tmp;
	int			exp_val;
	char		**tmp_val;
	char		**tmp_cmd;

	tmp_val = NULL;
	tmp_cmd = NULL;
	exp_val = ft_verif_expand_good(tmp);
	if (!ft_strcmp("export", tmp->cmd[0]) && tmp->cmd[i + 1]
		&& tmp->len_ind_exp >= 1 && exp_val == 0)
	{
		tmp_cmd = ft_all_one_ligne(param, tmp_cmd, tmp);
		tmp_val = ft_exp_split_par(tmp_cmd[0], param->mal);
		len_tmp = 0;
		ft_count_len(&len_tmp, tmp_val);
		tmp_cmd = ft_create_tmp_cmd(tmp_cmd, i, len_tmp, param->mal);
		param->i_ex = i + len_tmp;
		end_verif_exp(param, tmp_cmd, tmp_val, len_tmp);
		ft_free_realoc(param, tmp, tmp_cmd);
	}
}
