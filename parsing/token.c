/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:14:20 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/29 15:21:11 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int    ft_len_word(const char *s, int start)
{
    int		i;
    int		cmp;
	char	c;

    i = start;
    cmp = 0;
	if (s[i] == '"' || s[i] == 39)
	{
		c = s[i++];
		cmp++;
		while (s[i] && s[i] != c)
		{
			i++;
			cmp++;
		}
		i++;
		cmp++;
		return (cmp);
	}
	if (s[i] == '<' || s[i] == '>')
	{
		while (s[i] && (s[i] == '<' || s[i] == '>'))
		{
			i++;
			cmp++;
		}
		return (cmp);
	}
    while (s[i] && !is_white(s[i]) && s[i] != '<' && s[i] != '>')
    {
        i++;
        cmp++;
    }
	return (cmp);
}

int	get_tab_len(char *tab)
{
    int    i;
	char	c;
    int    count;

    i = 0;
    count = 0;
    while (tab[i])
    {
		if (tab[i] == '"' || tab[i] == 39)
		{
			c = tab[i++];
			count++;
			while (tab[i] && tab[i] != c)
				i++;
			i++;
			continue;
		}
		if ((tab[i] == '<' || tab[i] == '>') && tab[i + 1] != tab[i])
		{
			count++;
			i++;
			continue;
		}
        if (!is_white(tab[i]) && (is_white(tab[i + 1]) || tab[i + 1] == '\0'))
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
	int i;
	int	j;
	int	k;
	int	len;
	int	tab_len;

	i = 0;
	j = 0;
	tab_len = get_tab_len(tab);
	tmp->cmd = ft_calloc(tab_len + 1, sizeof(char *));
	if (!tmp->cmd)
		return ;
	while (i < tab_len)
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

void	get_token(t_init *param)
{
	int			i;
	t_list_char	*tmp;

	i = 0;
	param->tab = ft_split(param->line);
	param->count_cmd = get_nb_cmd(param->tab);
	param->tok = set_lst(param->count_cmd);
	tmp = param->tok;
	while (i < param->count_cmd)
	{
		set_cmd(param->tab[i], tmp);
		i++;
		tmp = tmp->next;
	}
}
