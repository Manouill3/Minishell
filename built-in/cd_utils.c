/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:48:34 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/27 14:49:00 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*ft_split_home_way(char **path_split, int i, int *j, char *lst, t_mal *mal)
{
	int	start;

	start = 0;
	if (path_split[i][(*j)] == lst[start])
	{
		while (path_split[i][(*j)] == lst[start])
		{
			if (path_split[i][(*j) + 1] == '/')
			{
				(*j) = (*j) + 2;
				while (path_split[i][(*j)] != '/')
					(*j)++;
				return (ft_substr(path_split[i], 0, (*j), mal));
			}
			(*j)++;
			start++;
		}
	}
	(*j)++;
	return (NULL);
}

char	*ft_give_home_way(char **path_split, char *lst, t_mal *mal)
{
	int		i;
	int		j;
	char	*path_home;

	i = 0;
	path_home = NULL;
	while (path_split[i])
	{
		j = 0;
		while (path_split[i][j])
		{
			path_home = ft_split_home_way(path_split, i, &j, lst, mal);
			if (path_home != NULL)
				return (path_home);
		}
		i++;
	}
	return (NULL);
}

char	*ft_path_user(char *path, t_list_char *tok, t_mal *mal)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	if (tok->cmd[1][0] == '/')
		tmp = ft_strjoin(path, tok->cmd[1], mal);
	else
	{
		len = ft_strlen(tok->cmd[1]);
		tmp = add_calloc(mal, sizeof(char), (len + 2));
		if (!tmp)
			return (NULL);
		tmp[0] = '/';
		while (tok->cmd[1][i])
		{
			tmp[j] = tok->cmd[1][i];
			j++;
			i++;
		}
	}
	return (tmp);
}

int	check_inside_path(char *path, t_list_char *tok)
{
	int	len;
	int	result;

	len = ft_strlen(path) - 1;
	result = ft_strncmp(path, tok->cmd[1], len);
	return (result);
}

int	ft_cd_last(t_init *param, t_list_char *tok, char *path)
{
	int	result;

	(void)path;;
	result = chdir(tok->cmd[1]);
	if (result == -1)
	{
		param->status = 1;
		perror("cd");
		return (0);
	}
	return (1);
}
