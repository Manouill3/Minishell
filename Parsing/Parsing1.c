/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:35:41 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/03 09:19:57 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_parsing_operator(t_init *init)
{
	int i;

	i = ft_strlen(init->tok->data);
	if (init->tok->data[0] == '|' && i >= 3)
	{
		if (i > 1 && init->tok->data[1] != '|' && i >= 3 )
			perror("Operator");
	}
	if (init->tok->data[0] == '<')
	{
		if (i > 1 && init->tok->data[1] != '<' && i >= 3)
			perror("Operator");
	}
	if (init->tok->data[0] == '>')
	{
		if (i > 1 && init->tok->data[1] != '>' && i >= 3)
			perror("Operator");
	}
	ft_get_start(&init->tok);
}

void	ft_parsing_flag(t_init *init)
{
	int i;

	i = ft_strlen(init->tok->data);
	if (i == 1)
		init->tok->name = "arg";
	if (i > 1 && i < 3 && ft_isalpha(init->tok->data[1] == 0))
		perror("flag");
	ft_get_start(&init->tok);
}

void    ft_parsing_line(t_init *init, char **env)
{
	token(init);
	get_env(init, env);
	// if (ft_strcmp(init->tok->name, "flag"))
	// 	ft_parsing_flag(init);
	// if (ft_strcmp(init->tok->name, "Operator"))
	// 	ft_parsing_operator(init);
	
}
