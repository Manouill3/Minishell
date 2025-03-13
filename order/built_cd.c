/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:37:36 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/13 11:10:32 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_rest_way_cd(t_list_char *lst, char *new_tmp)
{
	char	*tmp_pwd;

	if (lst->next->data[0] != '/')
	{
		tmp_pwd = ft_strjoin(new_tmp, "/");
		free(new_tmp);
		new_tmp = NULL;
		new_tmp = ft_strjoin(tmp_pwd, lst->next->data);
		free(tmp_pwd);
		tmp_pwd = NULL;
		chdir(new_tmp);
		free(new_tmp);
	}
	else
	{
		tmp_pwd = ft_strjoin(new_tmp, lst->next->data);
		free(new_tmp);
		chdir(tmp_pwd);
		free(tmp_pwd);
	}
}

void    ft_cd(t_list_char *lst)
{
	int		len_pwd;
	char	*new_tmp;
	
	ft_pwd();
	new_tmp = get_pwd();
	len_pwd = 0;
	if (lst->next == NULL)
	{
		perror("cd");
		free(new_tmp);
		exit(1);
	}
	if (lst->next->data != NULL)
	{
		ft_rest_way_cd(lst, new_tmp);
		ft_pwd();
	}
}
