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
	if(!ft_strcmp(tok->funct, "echo"))
                ft_echo(param, tok);
	if(!ft_strcmp(tok->funct, "cd"))
                ft_cd(param, tok);
	if(!ft_strcmp(tok->funct, "pwd"))
                ft_pwd();
	if(!ft_strcmp(tok->funct, "export"))
                ft_export(param, tok);
	if(!ft_strcmp(tok->funct, "unset"))
                ft_unset(param, tok);
	if(!ft_strcmp(tok->funct, "env"))
                ft_env(param->lst_env);
	if(!ft_strcmp(tok->funct, "exit"))
                ft_exit(param);
}
