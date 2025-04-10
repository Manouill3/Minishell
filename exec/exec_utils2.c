/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:17:24 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/10 16:12:27 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	get_tty(void)
{
	int tty_fd;
	
	if (!isatty(STDIN_FILENO))
    {
        tty_fd = open("/dev/tty", O_RDONLY);
        if (tty_fd == -1)
        {
            perror("Erreur d'ouverture de /dev/tty");
            return ;
        }
        dup2(tty_fd, STDIN_FILENO);
        close(tty_fd);
    }
    if (!isatty(STDOUT_FILENO))
    {
        tty_fd = open("/dev/tty", O_WRONLY);
        if (tty_fd == -1)
        {
            perror("Erreur d'ouverture de /dev/tty");
            return ;
        }
        dup2(tty_fd, STDOUT_FILENO);
        close(tty_fd);
    }
}
