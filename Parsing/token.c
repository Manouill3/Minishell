/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:53:40 by tcybak            #+#    #+#             */
/*   Updated: 2025/02/24 11:33:06 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    token(t_init *init)
{
    int i;
    int j;

    i = 0;
    init->line = ft_strtrim(init->line, " ");
    j = ft_strlen(init->line);
    // while (i < j)
    // {
        init->line = ft_strtrim(init->line, " ");
        j = ft_strlen(init->line);
        if (ft_strncmp(init->line, "echo", 3) == 0)
        {
            init->cmds[i]
            printf("Hello\n");
            i++;
        }
    // }
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