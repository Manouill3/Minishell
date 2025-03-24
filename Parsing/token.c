/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:53:40 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/24 14:24:57 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	print_lst(t_list_char *lst)
{
	t_list_char	*curr;

	curr = lst;
	while (curr)
	{
		printf("name : %s\n", curr->name);
		printf("data : %s\n", curr->data);
		curr = curr->next;
	}
}

void get_env(t_init *init, char **env)
{
	int	i;

	i = 0;;
	init->env = NULL;
	while (env[i])
	{
		ft_lstadd_back_char(&init->env, ft_lstnew_char(ft_strdup(env[i])));
		i++;
	}
	// while (init->env)
	// {
	// 	printf("env = %s\n", init->env->data);
	// 	init->env = init->env->next;
	// }
}

void	ft_check_name(t_init *init)
{
	t_list_char *new_node;
	
	new_node = ft_lstnew_char(ft_expand(init));
	if (init->tab[init->i][0] == '<' || init->tab[init->i][0] == '>' || init->tab[init->i][0] == '|')
		new_node->name = "Operator";
	else if (init->tab[init->i][0] == '-')
		new_node->name = "flag";
	else if (init->i == 0 || init->tab[init->i - 1][0] == '|')
		new_node->name = "cmd";
	else
		new_node->name = "arg";
	ft_lstadd_back_char(&init->tok, new_node);
}

void    token(t_init *init)
{	
	init->tok = NULL;
	init->tab = ft_split(init->line);
	init->i = 0;
	while (init->tab[init->i])
	{
		ft_check_name(init);
		init->i++;
	}	
}

