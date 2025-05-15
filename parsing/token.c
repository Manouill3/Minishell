/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:14:20 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/14 23:29:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	tab_len_quote(char *tab, int i, int	*count)
{
	char	c;
	int		save;

	save = i;
	c = tab[i++];
	while (tab[i] && tab[i] != c)
		i++;
	if (tab[i])
		i++;
	if ((tab[i] && is_white(tab[i])) || tab[i] == '\0')
	{
		(*count)++;
		return (i);
	}
	if (!tab[i] && i - save > 2)
		(*count)++;
	if (i - save == 1 && !is_white(tab[save - 1]))
		(*count)++;
	return (i);
}

int	get_tab_len(char *tab)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (tab[i] == '"' || tab[i] == 39)
		{
			i = tab_len_quote(tab, i, &count);
			continue ;
		}
		if ((tab[i] == '<' || tab[i] == '>') && tab[i + 1] != tab[i])
		{
			count++;
			i++;
			continue ;
		}
		if (!is_white(tab[i])
			&& (tab[i + 1] == '>' || tab[i + 1] == '<'
				|| is_white(tab[i + 1]) || tab[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

t_list_char	*set_lst(int count_cmd)
{
	int			i;
	t_list_char	*lst;

	i = 0;
	lst = NULL;
	while (i < count_cmd)
	{
		ft_lstadd_back_char(&lst, ft_lstnew_char(NULL));
		i++;
	}
	return (lst);
}

void	set_cmd(char *tab, t_list_char *tmp)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	j = 0;
	tmp->len_cmd = get_tab_len(tab);
	tmp->cmd = ft_calloc(tmp->len_cmd + 1, sizeof(char *));
	if (!tmp->cmd)
		return ;
	while (i < tmp->len_cmd)
	{
		k = 0;
		while (tab[j] && is_white(tab[j]))
			j++;
		len = ft_len_word(tab, j);
		tmp->cmd[i] = ft_calloc(len + 1, sizeof(char));
		if (!tmp->cmd[i])
			return ;
		while (k < len)
			tmp->cmd[i][k++] = tab[j++];
		i++;
	}
}

int	get_token(t_init *param)
{
	int			i;
	t_list_char	*tmp;

	i = 0;
	param->tab = ft_split(param->line);
	if (verif_nb_quote(param->tab))
	{
		param->tok = NULL;
		return (1);
	}
	param->count_cmd = get_nb_cmd(param->tab);
	param->tok = set_lst(param->count_cmd);
	tmp = param->tok;
	while (i < param->count_cmd)
	{
		set_cmd(param->tab[i], tmp);
		i++;
		tmp = tmp->next;
	}
	return (0);
}
