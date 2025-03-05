/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:35:41 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/04 15:48:03 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_parsing_operator(char *data)
{
	int i;

	i = ft_strlen(data);
	if (data[0] == '|')
	{
		if ((i > 1 && data[1] != '|') || (i >= 3))
			perror("bad operator 1");
	}
	if (data[0] == '<')
	{
		if ((i > 1 && data[1] != '<') || (i >= 3))
			perror("bad operator 2");
	}
	if (data[0] == '>')
	{
		if ((i > 1 && data[1] != '>') || (i >= 3))
			perror("bad operator 3");
	}
}

void	ft_parsing_flag(char *name, char *data)
{
	int i;

	i = ft_strlen(data);
	if (i == 1)
		name = "arg";
	if (i != 2 && !ft_isalpha(data[1]))
	{
		perror("flag");
		name = "arg";
	}
}

void    ft_parsing_line(t_init *init, char **env)
{
	t_list_char *tmp;

	get_env(init, env);
	token(init);
	tmp = init->tok;
	while (tmp)
	{
		printf("checkname :%s\n", tmp->name);
		printf("checkdata :%s\n", tmp->data);
		if (!ft_strcmp(tmp->name, "flag"))
			ft_parsing_flag(tmp->name, tmp->data);
		if (!ft_strcmp(tmp->name, "Operator"))
			ft_parsing_operator(tmp->data);
		tmp = tmp->next;
	}
	ft_heredoc(init->tok);
	ft_expand(init->tok, init->env);
	ft_lstclear_char(&init->tok);
	ft_lstclear_char(&init->env);
	ft_free_tab(init->tab);
}
