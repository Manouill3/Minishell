/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:03:52 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/10 11:03:44 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_wait_child(t_init *param)
{
    int        status;
    pid_t    last_pid;

    last_pid = wait(&status);
    while (last_pid > 0)
    {
        if (WIFEXITED(status) && last_pid == param->fds.pid)
            param->status = WEXITSTATUS(status);
        last_pid = wait(&status);
    }
}

char    **conv_lst_tab(t_env *env)
{
    int     i;
    char    *tmp_tab;
    t_env   *tmp;
    char    **tab;

    i = 0;
    tmp = env;
    while(tmp)
    {
        i++;
        tmp = tmp->next;
    }
    tab = ft_calloc(i + 1, sizeof(char *));
    if (!tab)
        return (NULL);
    tmp = env;
    i = 0;
    while(tmp)
    {
        tmp_tab = ft_strjoin(tmp->name, "=");
        tab[i++] = ft_strjoin(tmp_tab, tmp->cont);
        free(tmp_tab);
        tmp = tmp->next;
    }
    return(tab);
}

char    **make_path(t_env *env)
{
    t_env   *tmp;
    
    tmp = env;
    while (tmp)
    {
        if (!ft_strcmp("PATH", tmp->name))
            return (ft_normal_split(tmp->cont, ':'));
        tmp = tmp->next;
    }
    return (NULL);
}

char    **set_args(char **args, char **path)
{
    int i;
    char *tmp;
    char    *free_tmp;

    i = 0;
    if (!access(args[0], X_OK | F_OK))
        return (args);
    if (!args[0])
    {
        free_tab(args);
        return(NULL);
    }
    while (path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        free_tmp = tmp;
        tmp = ft_strjoin(tmp, args[0]);
        free(free_tmp);
        if (access(tmp, X_OK | F_OK) != -1)
        {
            free(args[0]);
            args[0] = tmp;
            return (args);
        }
        free(tmp);
        i++;
    }
    return (args);
}

void    verif_fd(int count, t_init *param)
{
    if (count == 0 && param->tok->fd_infile == -1)
        close_all(param, param->tok);
    if (count == param->count_cmd - 1 && param->tok->fd_outfile == -1)
        close_all(param, param->tok);
}
