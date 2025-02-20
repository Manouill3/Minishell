/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:35:41 by tcybak            #+#    #+#             */
/*   Updated: 2025/02/20 15:31:33 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_parsing_line(t_init *init)
{
    init->cmds = ft_split(init->line, ' ');
    if (init->cmds == NULL)
    {
        if (!init->line)
            perror("|");
        ft_free(init);
    }
    init->i = 0;
    while(init->cmds[init->i])
    {
        printf("%s\n",init->cmds[init->i]);
        init->i++;
    }
}
