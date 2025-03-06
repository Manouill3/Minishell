/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:24:26 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/06 16:46:17 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_free(t_init *init)
{
	if (init->pwd)
		free(init->pwd);
	if (init->line)
		free(init->line);
	if (init)
		free(init);
	return ;
}

void    ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
void    ft_free_all(t_init *init)
{
	if (init->tok)
		ft_lstclear_char(&init->tok);
	if (init->env)
		ft_lstclear_char(&init->env);
	if (init->heredoc)
		free(init->heredoc);
	if (init->pwd)
		free(init->pwd);
	if (init->line)
		free(init->line);
	if (init->tab)
		ft_free_tab(init->tab);
}
