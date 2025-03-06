/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:12:50 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/06 18:11:55 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"


void	ft_heredoc_oef_before(t_heredoc *heredoc, int i)
{
	while (1)
	{
		heredoc->input = readline("heredoc>");
		if (!heredoc->input || !ft_strcmp(heredoc->input, heredoc->eof[i]))
		{
			if (heredoc->input)
				free(heredoc->input);
			break;
		}
		free(heredoc->input);
	}
}

void	ft_heredoc_oef_last(t_heredoc *heredoc, int i)
{
	while (1)
	{
		heredoc->input = readline("heredoc>");
		if (!heredoc->input || !ft_strcmp(heredoc->input, heredoc->eof[i]))
		{
			if (heredoc->input)
				free(heredoc->input);
			break;
		}
		ft_putendl_fd(heredoc->input, heredoc->fd);
		free(heredoc->input);
	}
	close(heredoc->fd);
}

void	ft_heredoc(t_heredoc *heredoc)
{
	int	i;
	
	i = 0;
	heredoc->name = ft_get_name();
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
	int		count;
	t_list_char *tmp;

	tmp = lst;
	i = 0;
	count = count_heredoc(lst);
	heredoc->eof = ft_calloc(count + 1, sizeof(char *));
	if (!heredoc->eof)
		return ;
	while(tmp)
	{
		if (!ft_strcmp(tmp->name, "Operator") && !ft_strcmp("<<", tmp->data))
		{
			if (!tmp->prev || ((ft_strcmp(tmp->prev->name, "cmd") && ft_strcmp(tmp->prev->name, "flag"))) || !tmp->next)
				perror("heredoc");
			else
			{
				heredoc->eof[i] = tmp->next->data;
				i++;
			}
		}
		tmp = tmp->next;
	}
}

