/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:12:50 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/05 15:38:52 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"


void	ft_heredoc_oef_before(t_heredoc *heredoc, int i)
{
	while (1)
	{
		heredoc->input = readline("heredoc>");
		if (!heredoc->input || ft_strcmp(heredoc->input, heredoc->eof[i]))
		{
			if (heredoc->input)
				free(heredoc->input);
			break;
		}
		// printf("input : %s\n", heredoc->input);
		free(heredoc->input);
	}
}

void	ft_heredoc_oef_last(t_heredoc *heredoc, int i)
{
	while (1)
	{
		heredoc->input = readline("heredoc>");
		if (!heredoc->input || ft_strcmp(heredoc->input, heredoc->eof[i]))
		{
			if (heredoc->input)
				free(heredoc->input);
			break;
		}
		// printf("input last : %s\n", heredoc->input);
		ft_putendl_fd(heredoc->input, heredoc->fd);
		free(heredoc->input);
	}
}

void	ft_heredoc(t_heredoc *heredoc)
{
	int	i;
	
	i = 0;
	heredoc->name = ft_get_name();
	// printf("name : %s\n",heredoc->name);
	heredoc->fd = open(heredoc->name, O_CREAT, O_WRONLY);
	while (heredoc->eof[i])
	{
		if (heredoc->eof[i + 1] != NULL)
		ft_heredoc_oef_before(heredoc, i);
		else
		ft_heredoc_oef_last(heredoc, i);
		i++;
	}
}

void    ft_check_heredoc(t_list_char *lst, t_heredoc *heredoc)
{
	int			i;
	t_list_char *tmp;

	tmp = lst;
	i = 0;
	while(tmp)
	{
		if (!ft_strcmp(tmp->name, "Operator") && !ft_strcmp("<<", tmp->data))
		{
			if (!tmp->prev || ((ft_strcmp(tmp->prev->name, "cmd") && ft_strcmp(tmp->prev->name, "flag"))) || !tmp->next)
				perror("heredoc");
			else
			{
				tmp->next->data = heredoc->eof[i];
				i++;
			}
		}
		tmp = tmp->next;
	}
}
