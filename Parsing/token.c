/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:53:40 by tcybak            #+#    #+#             */
/*   Updated: 2025/02/24 17:17:22 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    token(t_init *init)
{
	int     i;
	int     j;
	char	*tmp;
	t_list_char	**cmds = NULL;
	t_list_char *test;
	

	i = 0;
	j = ft_strlen(init->line);
	while (i < j)
	{
		tmp = init->line;
		init->line = ft_strtrim(tmp, " ");
		free(tmp);
		if (ft_strncmp(init->line, "echo", 3) == 0)
		{
			ft_strlcpy(tmp, init->line, 4);
			if (!cmds)
			{
				*cmds = ft_lstnew_char(tmp);
				test = *cmds;
			}
			else 
				ft_lstadd_back_char(cmds, ft_lstnew_char(tmp));
			i += 4;
		}
		i = j + 10;
	}
	while (test != NULL)
	{
		printf("%s -> ", test->data);
		test = test->next;
	}
}

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