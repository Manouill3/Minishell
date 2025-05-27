/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:49:48 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/27 15:01:59 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_good(t_init *param, int good, char *old_path)
{
	if (good == 0)
		param->status = 1;
	else if (good == 1)
		ft_modif_pwd(param, old_path);
}

char	*ft_path_null(t_init *param)
{
	char	*path;
	t_env	*tmp_env;

	tmp_env = param->lst_env;
	while (tmp_env && ft_strcmp("OLDPWD", tmp_env->name))
		tmp_env = tmp_env->next;
	path = ft_strdup(tmp_env->cont, param->mal);
	if (!path)
		return (NULL);
	return (path);
}

char	*ft_old_path_null(t_init *param)
{
	char	*path;
	t_env	*tmp_env;

	tmp_env = param->lst_env;
	while (tmp_env && ft_strcmp("PWD", tmp_env->name))
		tmp_env = tmp_env->next;
	path = ft_strdup(tmp_env->cont, param->mal);
	if (!path)
		return (NULL);
	return (path);
}
