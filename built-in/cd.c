/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:14:23 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/09 11:18:25 by tcybak           ###   ########.fr       */
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
	free(path);
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

void	ft_cd(t_init *param, t_list_char *tok)
{
	int		result;
	char	*path;
	char	**path_split;

	result = 0;
	path = get_pwd();
	path_split = NULL;
	if (tok->len_cmd > 2)
	{
		free(path);
		param->status = 1;
		write(2, " too many arguments", 19);
	}
	else if (tok->cmd[1] == NULL || !ft_strcmp(tok->cmd[1], "~"))
		ft_cd_alone(path, path_split, param, result);
	else if (tok->cmd[1] != NULL && check_inside_path(path, tok) != 0)
		ft_cd_rest(param, tok, path, result);
	else if (check_inside_path(path, tok) == 0)
		ft_cd_last(param, tok, result, path);
	else
	{
		free(path);
		param->status = 1;
		perror("cd");
	}
}