/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/17 15:52:14 by tcybak           ###   ########.fr       */
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
		line = ft_strtrim(line, " ");
		if(ft_strcmp(line, "exit") == 0)
			exit(0); // prendre en compte espace avant 
	}
}
