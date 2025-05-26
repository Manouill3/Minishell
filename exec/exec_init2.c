/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:14:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/24 22:12:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	no_red_len(char **tab, t_list_char *tmp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < tmp->len_cmd)
	{
		if (ft_strlen(tab[i]) < 1)
		{
			i++;
			continue ;
		}
		if (tab[i] && ft_strcmp(tab[i], ">") && ft_strcmp(tab[i], "<"))
			len++;
		else
			i++;
		i++;
	}
	return (len);
}

void	no_red_ann(int len, t_list_char *tmp, t_init *param)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j < len && i < tmp->len_cmd)
	{
		if (ft_strlen(tmp->cmd[i]) < 1)
		{
			i++;
			continue ;
		}
		if (ft_strcmp(">", tmp->cmd[i]) && ft_strcmp("<", tmp->cmd[i])
			&& ft_strcmp(">>", tmp->cmd[i]) && ft_strcmp("<<", tmp->cmd[i]))
			tmp->no_red[j++] = ft_strdup(tmp->cmd[i], param->mal);
		else
			i++;
		i++;
	}
}

void	get_no_red(t_list_char *tok, t_init *param)
{
	t_list_char	*tmp;
	int			len;

	tmp = tok;
	while (tmp)
	{
		len = no_red_len(tmp->cmd, tmp);
		tmp->no_red = add_calloc(param->mal, len + 1, sizeof(char *));
		if (!tok->no_red)
			return ;
		no_red_ann(len, tmp, param);
		tmp = tmp->next;
	}
}

void	ft_exec_built_in(t_init *param, t_list_char *tok)
{
	if (!ft_strcmp(tok->funct, "echo"))
		ft_echo(param, tok);
	if (!ft_strcmp(tok->funct, "cd"))
		ft_cd(param, tok);
	if (!ft_strcmp(tok->funct, "pwd"))
		ft_pwd(param);
	if (!ft_strcmp(tok->funct, "export"))
		ft_export(param, tok);
	if (!ft_strcmp(tok->funct, "unset"))
		ft_unset(param, tok);
	if (!ft_strcmp(tok->funct, "env"))
		ft_env(param->lst_env);
	if (!ft_strcmp(tok->funct, "exit"))
		ft_exit(param);
}
