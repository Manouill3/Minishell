/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:12:50 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/18 10:55:02 by mdegache         ###   ########.fr       */
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

char	*get_eof(char *data, char *eof)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	eof = ft_calloc(ft_strlen(data) + 1, sizeof(char));
	while (data[i])
	{
		if (data[i] != '"' && data[i] != 39)
		{
			eof[j] = data[i];
			j++;
		}
		i++;
	}
	return (eof);
}


void    ft_check_heredoc(t_list_char *lst, t_heredoc *heredoc)
{
	int			i;
	int		count;
	t_list_char *tmp;

	tmp = lst;
	i = 0;
	count = count_heredoc(lst);
	if (count > 0)
	{
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
					heredoc->eof[i] = get_eof(tmp->next->data, heredoc->eof[i]);
					if (!heredoc->eof[i][0])
					{
						tmp = tmp->next;
						free(heredoc->eof[i]);
						heredoc->eof[i] = NULL;
						heredoc->eof[i] = get_eof(tmp->next->data, heredoc->eof[i]);
					}
					i++;
				}
			}
			tmp = tmp->next;
		}
		if (heredoc->eof[0] != NULL)
			ft_heredoc(heredoc);
	}
}
