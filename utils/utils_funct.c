/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:21:37 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/03 09:25:05 by mdegache         ###   ########.fr       */
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
		printf("funct : %s\n", curr->funct);
		curr = curr->next;
	}
}

int	len_cmd(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (*s1 == 0)
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
	count = 1;
	while (tab[i])
	{
		if (ft_strcmp("|", tab[i]) == 0)
			count++;
		i++;
	}
	return (count);
}

