/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:43:24 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/27 15:06:33 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_pwd(t_init *param)
{
	char	*way;
	char	*tmp;

	way = getcwd(NULL, 0);
	if (!way)
	{
		free(way);
		param->status = 1;
		return (NULL);
	}
	tmp = ft_strdup(way, param->mal);
	free(way);
	return (tmp);
}

void	ft_pwd(t_init *param)
{
	char	*pwd;

	pwd = get_pwd(param);
	printf("%s\n", pwd);
}
