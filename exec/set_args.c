/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:38:55 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/16 10:42:31 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*verif_path_split(int len, int j, char *tmp, char **args)
{
	while(args[0][len])
	{
		tmp[j] = args[0][len];
		j++;
		len++;
	}
	return (tmp);
}

int	verif_path(char **args, t_init *param)
{
	int		len;
	int		j;
	char	*tmp;
	
	if (args[0][0] != '.')
	{
		len = ft_strlen(args[0]);
		tmp = ft_calloc((len + 2), sizeof (char));
		if (!tmp)
			return (0);
		tmp[0] = '.';
		j = 1;
		len = 0;
		tmp = verif_path_split(len, j, tmp, args);
		if (access(tmp, F_OK) && args[0][0] == '/')
		{
			free(tmp);
			write(2, " Not a directory", 16);
			param->status = 126;
			return (1);
		}
		free(tmp);
	}
	return (0);
}

char	**set_args_ann2(char **args, t_init *param)
{
	if (verif_path(args, param) == 1)
		return (args);
	if (!access(args[0], F_OK) && access(args[0], X_OK) && (args[0][0] == '.'
			&& args[0][1] == '/'))
	{
		write(2, " Permission denied", 18);
		param->status = 126;
	}
	else
	{
		if ((args[0][0] == '.' || args[0][0] == '/'))
			write(2, " No such file or directory\n", 27);
		else
			write(2, " command not found\n", 19);
		param->status = 127;
	}
	return (args);
}

char	**set_args_ann(char **args, char **path, t_init *param, char *free_tmp)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!args[0])
	{
		free_tab(args);
		return (NULL);
	}
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		free_tmp = tmp;
		tmp = ft_strjoin(tmp, args[0]);
		free(free_tmp);
		if (access(tmp, X_OK | F_OK) != -1)
		{
			free(args[0]);
			args[0] = tmp;
			return (args);
		}
		free(tmp);
		i++;
	}
	return (set_args_ann2(args, param));
}

char	**set_args(char **args, char **path, t_init *param)
{
	struct stat	mode;
	char	*free_tmp;

	if (!path)
		return (args);
	free_tmp = NULL;
	if (args[0] && !access(args[0], X_OK | F_OK))
	{
		if (stat(args[0], &mode) == -1)
			return (NULL);
		if ((args[0][0] != '.' && args[0][0] != '/'))
		{
			if (!access(args[0], F_OK)
				&& (args[0][0] != '.' && args[0][1] != '/'))
				write(2, " command not found\n", 19);
			param->status = 127;
		}
		else if (S_ISDIR(mode.st_mode))
		{
			write(2, " Is a directory", 15);
			param->status = 126;
		}
		return (args);
	}
	return (set_args_ann(args, path, param, free_tmp));
}
