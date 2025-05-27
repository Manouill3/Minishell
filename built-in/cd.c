/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:14:23 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/27 14:46:41 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_cd_rest(t_init *param, t_list_char *tok, char *path)
{
	int		result;
	char	*tmp;

	tmp = ft_path_user(path, tok, param->mal);
	result = chdir(tmp);
	if (result == -1)
	{
		param->status = 1;
		// free(tmp);
		// free(path);
		perror("cd");
		return ;
	}
	// free(path);
	// free(tmp);
}

int	ft_cd_alone(char *path, char **path_split, t_init *param)
{
	int		result;

	// free(path);
	path = NULL;
	path_split = make_path(param->lst_env, param->mal);
	if (!path_split)
		return (0);
	path = ft_give_home_way(path_split, "homes", param->mal);
	// free_tab(path_split);
	if (!path)
		return (0);
	result = chdir(path);
	if (result == -1)
	{
		param->status = 1;
		perror("cd");
	}
	// free(path);
	return (1);
}

int	ft_delete_file(t_init *param, char *path, t_list_char *tok)
{
	if (!path && param->old_pwd)
	{
		path = NULL;
		path = param->old_pwd;
		ft_cd_rest(param, tok, path);
		return (1);
	}
	param->old_pwd = path;
	return (0);
}

void	ft_error(t_init *param, char *path, char *old_path)
{
	if (path)
		free(path);
	if (old_path)
		free(old_path);
	param->status = 1;
}

void	ft_cd(t_init *param, t_list_char *tok)
{
	char	*path;
	char	*old_path;
	char	**path_split;

	param->good_cd = 0;
	path = get_pwd(param);
	if (!path)
		path = ft_path_null(param);
	old_path = get_pwd(param);
	if (!old_path)
		old_path = ft_old_path_null(param);
	if (ft_delete_file(param, path, tok) == 1)
		return ;
	path_split = NULL;
	if (tok->len_cmd > 2)
		param->good_cd = ft_to_much_arg(param);
	else if (tok->cmd[1] == NULL || !ft_strcmp(tok->cmd[1], "~"))
		param->good_cd = ft_cd_alone(path, path_split, param);
	else if (tok->cmd[1] && !ft_strcmp(tok->cmd[1], "/"))
		param->good_cd = ft_cd_slash(param, path);
	else if (tok->cmd[1] != NULL && check_inside_path(path, tok) != 0)
		param->good_cd = ft_cd_rest2(param, tok, path);
	else if (check_inside_path(path, tok) == 0)
		param->good_cd = ft_cd_last(param, tok, path);
	ft_good(param, path, param->good_cd, old_path);
}
