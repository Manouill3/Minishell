/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:53:40 by tcybak            #+#    #+#             */
/*   Updated: 2025/02/25 13:41:36 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    token(t_init *init)
{
	int			i;
	// t_list_char	*cmds;
	// t_list_char *test;
	
	init->tab = ft_split(init->line, ' ');
	i = 0;
	while (init->tab[i])
	{
		printf("init->tab = %s i = %d\n", init->tab[i], i);
		i++;
	}
	ft_free_tab(init->tab);
}

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