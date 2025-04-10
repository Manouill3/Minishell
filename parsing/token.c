/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:14:20 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/01 14:27:18 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	get_tab_len(char **tab, int k)
{
	int	i;

	i = 0;
	while (tab[k] && ft_strcmp("|", tab[k]))
	{
		i++;
		k++;
	}
	return (i);
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

void	set_cmd(t_init *param, t_list_char *tmp, int *k)
{
	int	j;
	int	tab_len;

	j = 0;
	tab_len = get_tab_len(param->tab, (*k));
	tmp->cmd = malloc(sizeof(char *) * (tab_len + 1));
	while (j < tab_len)
	{
		tmp->cmd[j] = ft_strdup(param->tab[(*k)]);
		j++;
		(*k)++;
	}
	tmp->cmd[j] = NULL;
}

void	get_token(t_init *param)
{
	int			i;
	int			k;
	t_list_char	*tmp;

	i = 0;
	k = 0;
	param->tab = ft_split(param->line);
	param->count_cmd = get_nb_cmd(param->tab);
	param->tok = set_lst(param->count_cmd);
	tmp = param->tok;
	while (i < param->count_cmd)
	{
		set_cmd(param, tmp, &k);
		k++;
		i++;
		tmp = tmp->next;
	}
}
