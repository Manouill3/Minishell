/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:19:32 by marvin            #+#    #+#             */
/*   Updated: 2025/05/28 16:06:12 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_valid_char(char *buffer, t_mal *mal)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = add_calloc(mal, 10, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (buffer[j] && i < 9)
	{
		if (ft_isalnum(buffer[j]))
		{
			res[i] = buffer[j];
			i++;
		}
		j++;
	}
	return (res);
}

char	*get_name_h(t_mal *mal)
{
	char	*valid_name;
	char	buffer[1000];
	int		fd;
	int		bytes;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes = read(fd, buffer, 1000);
	if (bytes == -1)
		return (NULL);
	buffer[bytes] = '\0';
	valid_name = get_valid_char(buffer, mal);
	if (access(valid_name, F_OK))
	{
		close(fd);
		return (valid_name);
	}
	close(fd);
	return (get_name_h(mal));
}

void	get_nb_eof(t_list_char *tok)
{
	int			i;
	int			nb;
	t_list_char	*tmp;

	tmp = tok;
	while (tmp)
	{
		nb = 0;
		i = 0;
		while (tmp->cmd[i])
		{
			if (!ft_strcmp("<<", tmp->cmd[i]))
				nb++;
			i++;
		}
		tmp->heredoc->nb_eof = nb;
		tmp = tmp->next;
	}
}

void	get_eof_tab(t_list_char *tok, t_mal *mal)
{
	int			i;
	int			j;
	t_heredoc	*heredoc;

	i = 0;
	j = 0;
	heredoc = tok->heredoc;
	heredoc->eof = add_calloc(mal, heredoc->nb_eof + 1, sizeof(char *));
	if (!heredoc->eof)
		return ;
	while (tok->cmd[i])
	{
		if (!ft_strcmp("<<", tok->cmd[i]))
		{
			if (tok->cmd[i + 1])
				heredoc->eof[j++] = ft_strdup(tok->cmd[i + 1], mal);
		}
		i++;
	}
}

char	*get_final_eof(char *str, t_mal *mal)
{
	int		i;
	int		j;
	char	*eof;

	i = 0;
	j = 0;
	eof = add_calloc(mal, ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] != '"' && str[i] != 39)
		{
			eof[j] = str[i];
			j++;
		}
		i++;
	}
	return (eof);
}
