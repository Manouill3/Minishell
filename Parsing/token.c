/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:53:40 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/03 10:41:39 by mdegache         ###   ########.fr       */
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
		ft_lstadd_back_char(&init->env, ft_lstnew_char(env[i]));
		i++;
	}
}

void	ft_check_name(t_init **init)
{
	t_list_char *new_node;
	
	new_node = ft_lstnew_char((*init)->tab[(*init)->i]);
	if ((*init)->tab[(*init)->i][0] == '<' || (*init)->tab[(*init)->i][0] == '>' || (*init)->tab[(*init)->i][0] == '|')
		new_node->name = "Operator";
	else if ((*init)->tab[(*init)->i][0] == '-')
		new_node->name = "flag";
	else if ((*init)->i == 0 || (*init)->tab[(*init)->i - 1][0] == '|')
		new_node->name = "cmd";
	else
		new_node->name = "arg";
	ft_lstadd_back_char(&(*init)->tok, new_node);
}

void    token(t_init *init)
{	
	init->tok = NULL;
	init->tab = ft_split(init->line);
	init->i = 0;
	while (init->tab[init->i])
	{
		ft_check_name(&init);
		init->i++;
	}
	print_lst(init->tok);
}

//////////////////////////////
// {
// 	int     i;
// 	int     j;
// 	char	*tmp;
// 	t_list_char	*cmds;
// 	t_list_char *test;
	

// 	i = 0;
// 	j = ft_strlen(init->line);
// 	while (i < j)
// 	{
// 		tmp = init->line;
// 		init->line = ft_strtrim(tmp, " ");
// 		free(tmp);
// 		if (ft_strncmp(init->line, "echo", 4) == 0)
// 		{
// 			ft_strlcpy(tmp, init->line, 5);
// 			ft_lstadd_back_char(&cmds, ft_lstnew_char(tmp, "1"));
// 			i += 4;
// 		}
// 		i = j + 10;
// 	}
// 	test = cmds;
// 	while (test != NULL)
// 	{
// 		printf("data = %s -> name = %s\n", test->data, test->name);
// 		test = test->next;
// 	}
// 	free(test);
// 	test = cmds;
// }

// init->cmds = ft_split(init->line, ' ');
// if (init->cmds == NULL)
// {
//     if (!init->line)
//         perror("|");
//     ft_free(init);
// }
// init->i = 0;
// while(init->cmds[init->i])
// {
//     printf("%s\n",init->cmds[init->i]);
//     init->i++;
// }


////////////////////
// int     i;
// int     j;
// char    *tmp;

// i = 0;
// j = ft_strlen(init->line);
// while (i < j)
//  {
//     tmp = init->line;
//     init->line = ft_strtrim(tmp, " ");
//     free(tmp);
//     j = ft_strlen(init->line);
//     if (ft_strncmp(init->line, "echo", 4) == 0)
//     {
//         tmp = init->cmds;
//         init->cmds[i] = ft_strndup(init->line, 4);
//         printf("Token %s\n", (char *)init->cmds[i]);
//         i++;
//     }
//      i++;
//  }