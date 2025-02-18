/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:52 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/18 10:48:55 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_init
{
    char    *line;

}			t_init;

////////////////////////////////////////
///			utils/utils_parsing	    ///
//////////////////////////////////////

int ft_strcmp(char *s1, char *s2);
////////////////////////////////////////
///			Handle_signaux          ///
//////////////////////////////////////

void    ft_handle_interrupt_signals(void);

#endif