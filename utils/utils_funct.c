/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:21:37 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/08 15:18:42 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	print_lst_env(t_env *lst)
{
	t_env	*curr;

	curr = lst;
	while (curr)
	{
		printf("name : %s\n", curr->name);
		printf("cont : %s\n", curr->cont);
		curr = curr->next;
	}
}

void	print_lst_char(t_list_char *lst)
{
	int			i;
	t_list_char	*curr;

	curr = lst;
	while (curr)
	{
		i = 0;
		while (curr->cmd[i])
		{
			printf("cmd[%d] : %s\n", i, curr->cmd[i]);
			i++;
		}
		i = 0;
		while (curr->no_red[i])
		{
			printf("no_red[%d] : %s\n", i, curr->no_red[i]);
			i++;
		}
		printf("funct : %s\n", curr->funct);
		curr = curr->next;
	}
}

int	is_red(char *val)
{
	if (ft_strlen(val) <= 0)
		return (1);
	if (!ft_strcmp(val, ">"))
		return (0);
	if (!ft_strcmp(val, ">>"))
		return (0);
	if (!ft_strcmp(val, "<"))
		return (0);
	if (!ft_strcmp(val, "<<"))
		return (0);
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	if (!s1 || !s2)
		return (1);
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1 - s2);
		i++;
	}
	return (0);
}

int	get_nb_cmd(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		count++;
		i++;
	}
	return (count);
}

// int	only_white()
// {
	
// }
