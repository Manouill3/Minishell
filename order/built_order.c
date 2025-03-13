/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:56:21 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/13 11:20:55 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char    *get_pwd(void)
{
    char *way;
    char *path;
    
    way = getcwd(NULL, 0);
    if (!way) {
        free(way);
        perror("getcwd");
        return (NULL);
    }
    path = ft_strjoin(way, "$ ");
    free(way);
    return (path);
}

void ft_pwd()
{
    char *pwd;
    
    pwd = get_pwd();
    printf("%s\n", pwd);
    free(pwd);        
}
void    ft_check_order(t_init *init)
{
	t_list_char	*tmp;

	tmp = init->tok;
    while(tmp)
    {
        if (!ft_strcmp(tmp->data, "pwd") && !ft_strcmp(tmp->name, "cmd"))
            ft_pwd();
        if (!ft_strcmp(tmp->data, "cd") && !ft_strcmp(tmp->name, "cmd"))
            ft_cd(tmp);
        tmp = tmp->next;
    }    
    return ;
}
