/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:21:37 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/30 09:06:51 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

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

int	only_white(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_white(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	nb_exp(char **cmd)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			nb++;
			if (i > 0 && (!ft_strcmp(cmd[i - 1], "<<")
					|| !ft_strcmp(cmd[i - 1], "<")
					|| !ft_strcmp(cmd[i - 1], ">")
					|| !ft_strcmp(cmd[i - 1], ">>")))
				nb--;
		}
		i++;
	}
	return (nb);
}
