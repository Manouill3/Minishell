/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:49:48 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/24 22:21:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_good(t_init *param, char *path, int good, char *old_path)
{
	if (good == 0)
		ft_error(param, path, old_path);
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
