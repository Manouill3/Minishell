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

void    supp_quote_red(t_list_char *tok)
{
	t_list_char    *tmp;
	char           *str;
	int            i;
	int            j;

	tmp = tok;
	while (tmp)
	{
		i = 0;
		while(tmp->cmd[i])
		{
			if (!is_red(tmp->cmd[i]) && ft_strcmp(tmp->cmd[i], "<<"))
			{
				j = 0;
				while (tmp->cmd[i + 1][j])
				{
					if (tmp->cmd[i + 1][j] == '"' || tmp->cmd[i + 1][j] == 39)
					{
						str = char_out(tmp->cmd[i + 1], tmp->cmd[i + 1][j]);
						free(tmp->cmd[i + 1]);
						tmp->cmd[i + 1] = str;
						break ;
					}
					j++;
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}

int verif_odd(char **tab, int count1, int count2)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (count1 % 2 != 0)
		{
			if (count2 % 2 != 0 || count2 == 0)
				return (1);
		}
		if (count2 % 2 != 0)
		{
			if (count1 % 2 != 0 || count1 == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int    verif_nb_quote(char **tab)
{
	int    i;
	int    j;
	int    count1;
	int    count2;

	i = 0;
	count1 = 0;
	count2 = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '"')
				count2++;
			if (tab[i][j] == 39)
				count1++;
			j++;
		}
		i++;
	}
	if (verif_odd(tab, count1, count2))
		return (1);
	return (0);
}

void    ft_free_realoc(t_init *param, t_list_char *tmp, char **tmp_cmd, char **tmp_val)
{
	int i;

	i = 0;
	free_tab(tmp->cmd);
	free_tab(tmp->no_red);
	tmp->cmd = tmp_cmd;
	param->tok->funct = tmp->cmd[0];
	free(tmp_val);
	i = 0;
	while (tmp->cmd[i])
		i++;
	tmp->len_cmd = i;
	param->i_ex = 0;
}

void    ft_test(t_init *param, char **tmp_cmd, char **tmp_val, int len_tmp)
{
	int i;
	int j;
	t_list_char *tmp;

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

void    ft_count_len(int *len_tmp, int *i, char **tmp_val, t_list_char *tmp)
{
	while (tmp_val[(*len_tmp)])
		(*len_tmp)++;
	while (tmp->cmd[(*i) + 1])
		(*i)++;
}

char    **ft_create_tmp_cmd(char **tmp_cmd, int i, int len_tmp, char **tmp_val)
{
	tmp_cmd = ft_calloc((i + len_tmp + 1), (sizeof(char *)));
	if (!tmp_cmd)
	{
		free(tmp_val);
		return (NULL);
	}
	return (tmp_cmd);
}
void	verif_expand(t_init *param)
{
	int			i;
	int			len_tmp;
	char 		**tmp_val;
	char		**tmp_cmd;
	t_list_char	*tmp;

	i = 0;
	if (param->tok)
	{
		tmp = param->tok;
		while (i < param->len_ind_exp)
		{
			if (tmp->cmd[i] && ft_strcmp(tmp->funct,tmp->cmd[i]) && ft_strchr(tmp->cmd[i], ' ') && tmp->ind_exp[i] == i)
			{
				tmp_val = ft_normal_split(tmp->cmd[i], 32);
				free(tmp->cmd[i]);
				tmp->cmd[i] = NULL;
				len_tmp = 0;
				ft_count_len( &len_tmp, &i, tmp_val, tmp);
				tmp_cmd = ft_create_tmp_cmd(tmp_cmd, i, len_tmp, tmp_val);
				param->i_ex = i + len_tmp;
				ft_test(param, tmp_cmd, tmp_val, len_tmp);
				ft_free_realoc(param, tmp, tmp_cmd, tmp_val);
			}
			i++;
		}
	}
}
