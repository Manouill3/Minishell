/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:14:23 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/30 14:40:45 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_cd_rest(t_init *param, t_list_char *tok, char *path, int h)
{
	int		result;
	char	*tmp;

	tmp = ft_path_user(path, tok, param->mal, h);
	if (!tmp)
		return ;
	result = chdir(tmp);
	if (result == -1)
	{
		param->status = 1;
		perror("cd");
		return ;
	}
}

int	ft_cd_alone(char *path, char **path_split, t_init *param)
{
	int		result;

	path = NULL;
	path_split = make_path(param->lst_env, param->mal);
	if (!path_split)
		return (0);
	path = ft_give_home_way(path_split, param->mal);
	if (!path)
		return (0);
	result = chdir(path);
	if (result == -1)
	{
		param->status = 1;
		perror("cd");
	}
	return (1);
}

int	ft_delete_file(t_init *param, char *path, t_list_char *tok, int h)
{
	if (!path && param->old_pwd)
	{
		path = NULL;
		path = param->old_pwd;
		ft_cd_rest(param, tok, path, h);
		return (1);
	}
	param->old_pwd = path;
	return (0);
}

void	ft_cd(t_init *param, t_list_char *tok, int i, int j)
{
	char	*path;
	char	*old_path;
	char	**path_split;

	path = get_pwd(param);
	if (!path)
		path = ft_path_null(param);
	old_path = get_pwd(param);
	if (!old_path)
		old_path = ft_old_path_null(param);
	if (ft_delete_file(param, path, tok, i) == 1)
		return ;
	path_split = NULL;
	if (j > 2)
		param->good_cd = ft_to_much_arg(param);
	else if (tok->cmd[i + 1] == NULL || tok->cmd[i + 1][0] == '\0'
		|| !ft_strcmp(tok->cmd[i + 1], "~"))
		param->good_cd = ft_cd_alone(path, path_split, param);
	else if (tok->cmd[i + 1] && !ft_strcmp(tok->cmd[i + 1], "/"))
		param->good_cd = ft_cd_slash(param);
	else if (tok->cmd[i + 1] != NULL && check_inside_path(path, tok) != 0)
		param->good_cd = ft_cd_rest2(param, tok, path, i);
	else
		param->good_cd = ft_cd_last(param, tok);
	ft_good(param, param->good_cd, old_path);
}
