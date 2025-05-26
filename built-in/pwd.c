/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:43:24 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/24 22:33:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_pwd(t_init *param)
{
	char	*way;

	way = getcwd(NULL, 0);
	if (!way)
	{
		free(way);
		param->status = 1;
		return (NULL);
	}
	return (way);
}

void	ft_pwd(t_init *param)
{
	char	*pwd;

	pwd = get_pwd(param);
	printf("%s\n", pwd);
	free(pwd);
}
