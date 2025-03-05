/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:56:21 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/04 15:02:12 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_pwd(void)
{
    char *chemin = NULL;

    chemin = getcwd(NULL, 0); 
    printf("Le chemin du repertoire est %s\n", chemin);
    free(chemin);
}

void    ft_check_order(t_init *init)
{
    if (ft_strcmp(init->line, "pwd") == 0)
        ft_pwd();
    return ;
}