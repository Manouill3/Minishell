/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:39:52 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/19 11:26:08 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_to_much_arg(t_init *param, char *path)
{
	free(path);
	param->status = 1;
	write(2, " too many arguments", 19);
}

void	ft_cd_slash(t_init *param, char *path)
{
	int	result;

	result = chdir(param->tok->cmd[1]);
	if (result == -1)
	{
		param->status = 1;
		perror("cd");
	}
	free(path);
}
