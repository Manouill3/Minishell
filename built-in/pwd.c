/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 08:43:24 by tcybak            #+#    #+#             */
/*   Updated: 2025/04/08 08:44:40 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char    *get_pwd(void)
{
    char *way;
    
    way = getcwd(NULL, 0);
    if (!way) {
        free(way);
        perror("getcwd");
        return (NULL);
    }
    return (way);
}

void ft_pwd()
{
    char *pwd;
    
    pwd = get_pwd();
    printf("%s\n", pwd);
    free(pwd);        
}

void    ft_exec_built_in(t_init *param, t_list_char *tok)
{
	if(!ft_strcmp("echo", tok->funct))
        return ;
	if(!ft_strcmp("cd", tok->funct))
        ft_cd(param, tok);
	if(!ft_strcmp("pwd", tok->funct))
        ft_pwd();
	if(!ft_strcmp("export", tok->funct))
        return ;
	if(!ft_strcmp("unset", tok->funct))
        return ;
	if(!ft_strcmp("env", tok->funct))
        return ;
	if(!ft_strcmp("exit", tok->funct))
        return ;
}