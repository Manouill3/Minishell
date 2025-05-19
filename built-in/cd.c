/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:14:23 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/19 10:54:28 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_cd_rest(t_init *param, t_list_char *tok, char *path, int result)
{
	char	*tmp;

	tmp = ft_path_user(path, tok);
	result = chdir(tmp);
	if (result == -1)
	{
		param->status = 1;
		perror("cd");
	}
	free(tmp);
}

void	ft_cd_alone(char *path, char **path_split, t_init *param, int result)
{
	free(path);
	path = NULL;
	path_split = make_path(param->lst_env);
	path = ft_give_home_way(path_split, "homes");
	free_tab(path_split);
	result = chdir(path);
	if (result == -1)
	{
		param->status = 1;
		perror("cd");
	}
	free(path);
}

int	ft_delete_file(t_init *param, char *path, int result, t_list_char *tok)
{
	if (!path && param->old_pwd)
	{
		path = NULL;
		path = param->old_pwd;
		ft_cd_rest(param, tok, path, result);
		return (1);
	}
	param->old_pwd = path;
	return (0);
}

void	ft_error(t_init *param, char *path)
{
	free(path);
	param->status = 1;
	perror("cd");
}

void	ft_cd(t_init *param, t_list_char *tok)
{
	int		result;
	char	*path;
	char	**path_split;

	result = 0;
	path = get_pwd();
	if (ft_delete_file(param, path, result, tok) == 1)
		return ;
	path_split = NULL;
	if (tok->len_cmd > 2)
		ft_to_much_arg(param, path);
	else if (tok->cmd[1] == NULL || !ft_strcmp(tok->cmd[1], "~"))
		ft_cd_alone(path, path_split, param, result);
	else if (tok->cmd[1] != NULL && check_inside_path(path, tok) != 0)
	{
		ft_cd_rest(param, tok, path, result);
		free(path);
	}
	else if (check_inside_path(path, tok) == 0)
		ft_cd_last(param, tok, result, path);
	else
		ft_error(param, path);
}
