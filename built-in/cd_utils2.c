/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:39:52 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/26 10:05:20 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	ft_to_much_arg(t_init *param)
{
	param->status = 1;
	write(2, " too many arguments\n", 20);
	return (0);
}

int	ft_cd_slash(t_init *param, char *path)
{
	int	result;

	(void)path;
	result = chdir(param->tok->cmd[1]);
	if (result == -1)
	{
		param->status = 1;
		perror("cd");
		return (0);
	}
	// free(path);
	return (1);
}

void	ft_modif_split_pwd(t_init *param, char *old_path, char *pwd)
{
	t_env	*tmp_env;
	t_env	*tmp_exp;

	(void)old_path;
	tmp_env = param->lst_env;
	tmp_exp = param->lst_export;
	while (tmp_env && ft_strcmp("PWD", tmp_env->name))
		tmp_env = tmp_env->next;
	if (tmp_env && !ft_strcmp("PWD", tmp_env->name))
	{
		// free(tmp_env->cont);
		tmp_env->cont = NULL;
		tmp_env->cont = ft_strdup(pwd, param->mal);
	}
	while (tmp_exp && ft_strcmp("PWD", tmp_exp->name))
		tmp_exp = tmp_exp->next;
	if (tmp_env && !ft_strcmp("PWD", tmp_exp->name))
	{
		// free(tmp_exp->cont);
		tmp_exp->cont = NULL;
		tmp_exp->cont = ft_strdup(pwd, param->mal);
	}
	// free(pwd);
	// free(old_path);
}

void	ft_modif_pwd(t_init *param, char *old_path)
{
	char	*pwd;
	t_env	*tmp_env;
	t_env	*tmp_exp;

	tmp_env = param->lst_env;
	tmp_exp = param->lst_export;
	pwd = get_pwd(param);
	while (tmp_env && ft_strcmp("OLDPWD", tmp_env->name))
		tmp_env = tmp_env->next;
	if (tmp_env && !ft_strcmp("OLDPWD", tmp_env->name))
	{
		// free(tmp_env->cont);
		tmp_env->cont = NULL;
		tmp_env->cont = ft_strdup(old_path, param->mal);
	}
	while (tmp_exp && ft_strcmp("OLDPWD", tmp_exp->name))
		tmp_exp = tmp_exp->next;
	if (tmp_env && !ft_strcmp("OLDPWD", tmp_exp->name))
	{
		// free(tmp_exp->cont);
		tmp_exp->cont = NULL;
		tmp_exp->cont = ft_strdup(old_path, param->mal);
	}
	ft_modif_split_pwd(param, old_path, pwd);
}

int	ft_cd_rest2(t_init *param, t_list_char *tok, char *path)
{
	int		result;
	char	*tmp;

	tmp = ft_path_user(path, tok, param->mal);
	result = chdir(tmp);
	if (result == -1)
	{
		param->status = 1;
		perror("cd");
		free(tmp);
		return (0);
	}
	// free(tmp);
	// free(path);
	return (1);
}
