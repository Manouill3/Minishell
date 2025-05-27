/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:40:34 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/27 13:45:30 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	exec_supp_quote_red(t_list_char *tmp, int i, t_mal *mal)
{
	int			j;
	char		*str;

	if (!is_red(tmp->cmd[i]) && ft_strcmp(tmp->cmd[i], "<<"))
	{
		j = 0;
		while (tmp->cmd[i + 1][j])
		{
			if (tmp->cmd[i + 1][j] == '"' || tmp->cmd[i + 1][j] == 39)
			{
				str = char_out(tmp->cmd[i + 1], tmp->cmd[i + 1][j], mal);
				// free(tmp->cmd[i + 1]);
				tmp->cmd[i + 1] = str;
				break ;
			}
			j++;
		}
	}
}

void	supp_quote_red(t_list_char *tok, t_mal *mal)
{
	t_list_char	*tmp;
	int			i;

	tmp = tok;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			exec_supp_quote_red(tmp, i, mal);
			i++;
		}
		tmp = tmp->next;
	}
}

int	verif_odd(char **tab, int count1, int count2)
{
	int	i;

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

int	verif_nb_quote(char **tab)
{
	int	i;
	int	j;
	int	count1;
	int	count2;

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

void	ft_free_realoc(t_init *param, t_list_char *tmp,
		char **tmp_cmd, char **tmp_val)
{
	int	i;

	(void)tmp_val;
	i = 0;
	// free_tab(tmp->cmd);
	// free_tab(tmp->no_red);
	tmp->cmd = tmp_cmd;
	param->tok->funct = tmp->cmd[0];
	// free(tmp_val);
	i = 0;
	while (tmp->cmd[i])
		i++;
	tmp->len_cmd = i;
	param->i_ex = 0;
}
