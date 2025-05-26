/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:39:28 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/26 17:56:18 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



char    **ft_all_one_ligne(t_init *param, char **tmp_cmd, t_list_char *tmp)
{
	int	x;
	int	y;
	int	len;
	int i;
	
	x = 0;
	y = 0;
	len = 0;
	i = 0;
	while (tmp->cmd[x])
	{
		y = 0;
		while (tmp->cmd[x][y])
		{
			y++;
			len++;
		}
		len++;
		x++;
	}
	tmp_cmd = add_calloc(param->mal, sizeof(char *), 2);
	if (!tmp_cmd)
		return; 
	tmp_cmd[0] = add_calloc(param->mal,sizeof(char), (len + 1));
	if (!tmp_cmd[0])
		return;
	x = 0;
	len = 0;
	while (tmp->cmd && tmp->cmd[x])
	{
		y = 0;
		while (tmp->cmd && tmp->cmd[x][y])
		{
			tmp_cmd[0][len] = tmp->cmd[x][y];
			y++;
			len++;
		}
		tmp_cmd[0][len] = ' ';
		len++;
		x++;
	}
}

void	exec_verif_exp2(t_init *param, t_list_char *tmp, int i)
{

	int			len_tmp;
	char		**tmp_val;
	char		**tmp_cmd;

	tmp_val = NULL;
	tmp_cmd = NULL;

	if (!ft_strcmp("export", tmp->cmd[0]) && tmp->cmd[i + 1] && tmp->len_ind_exp >= 1)
	{
		tmp_cmd = ft_all_one_ligne(param, tmp_cmd, t_list_char *tmp);
		tmp_val = ft_exp_split(tmp_cmd[0], param->mal);
		tmp_cmd = NULL;
		tmp->cmd[i] = NULL;
		len_tmp = 0;
		ft_count_len(&len_tmp, &i, tmp_val, tmp);
		tmp_cmd = ft_create_tmp_cmd(tmp_cmd, i, len_tmp, tmp_val, param->mal);
		param->i_ex = i + len_tmp;
		end_verif_exp(param, tmp_cmd, tmp_val, len_tmp);
		ft_free_realoc(param, tmp, tmp_cmd, tmp_val);
	}
}