/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:12:50 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/04 10:19:58 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_heredoc(t_init *init)
{
    t_list_char *tmp;

    tmp = init->tok;
    if (!ft_strcmp(tmp->name, "Operator") && !ft_strcmp(tmp->data, "<<"))
    {
        if (tmp->prev->data == "cmd")
        
    }
}