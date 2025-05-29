/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:14:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/29 17:24:45 by tcybak           ###   ########.fr       */
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
		no_red_ann(len, tmp, param);
		tmp = tmp->next;
	}
}

void	ft_exec_built_in(t_init *param, t_list_char *tok)
{
	int	i;
	int	j;

	if (!ft_strcmp(tok->funct, "echo"))
		ft_echo(param, tok);
	if (!ft_strcmp(tok->funct, "cd"))
	{
		i = 0;
		j = 0;
		while (tok->cmd[i] && ft_strcmp("cd", tok->cmd[i]))
			i++;
		while (tok->cmd[i + j])
			j++;
		ft_cd(param, tok, i, j);
	}
	if (!ft_strcmp(tok->funct, "pwd"))
		ft_pwd(param);
	if (!ft_strcmp(tok->funct, "export"))
		ft_export(param, tok);
	if (!ft_strcmp(tok->funct, "unset"))
		ft_unset(param, tok);
	if (!ft_strcmp(tok->funct, "env"))
		ft_env(param, param->lst_env, tok);
	if (!ft_strcmp(tok->funct, "exit"))
		ft_exit(param, tok);
}

void	pipe_or_built(t_init *param, t_list_char *tmp, int count)
{
	while (tmp)
	{
		if (secu_cmd(tmp))
		{
			count++;
			tmp = tmp->next;
			continue ;
		}
		if (param->count_cmd == 1 && (verif_built(tmp) == 2
				|| verif_built(tmp) == 4
				|| verif_built(tmp) == 5 || verif_built(tmp) == 7))
		{
			ft_exec_built_in(param, tmp);
			tmp = tmp->next;
			continue ;
		}
		if (tmp->funct != NULL && ft_strlen(tmp->funct) > 0)
			count = ft_exec_pipe(tmp, param, count);
		else
			not_command(tmp);
		tmp = tmp->next;
	}
}
