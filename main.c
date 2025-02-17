/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/17 14:47:55 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minishell.h"

int main(void)
{
    char *line;
    
    line = NULL;
    while(1)
    {
        line = readline("Minishell:");
        if(ft_strcmp(line, "exit") == 0)
            exit(0); // prendre en compte espace avant 
    }
}
