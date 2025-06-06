/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:17:24 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/28 15:24:00 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	get_tty(void)
{
	int	tty_fd;

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

char	*get_last_eof(char **cmd)
{
	int		i;
	char	*last_eof;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp("<<", cmd[i]))
			last_eof = cmd[i + 1];
		i++;
	}
	return (last_eof);
}

int	get_infile_nb(char **cmd)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp("<", cmd[i]))
			nb++;
		if (!ft_strcmp("<<", cmd[i]))
			nb++;
		i++;
	}
	nb = nb * 2;
	return (nb);
}

int	get_outfile_nb(char **cmd)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(">", cmd[i]))
			nb++;
		if (!ft_strcmp(">>", cmd[i]))
			nb++;
		i++;
	}
	nb = nb * 2;
	return (nb);
}

void	not_command(t_list_char *tmp)
{
	int	i;

	i = 0;
	while (tmp->cmd[i] && ft_strlen(tmp->cmd[i]) < 1)
		i++;
	if ((!ft_strcmp(tmp->cmd[i], ">") || !ft_strcmp(tmp->cmd[i], "<"))
		&& (ft_strchr(tmp->cmd[i + 1], '>')
			|| ft_strchr(tmp->cmd[i + 1], '<')))
		ft_putstr_fd("command not found\n", 2);
}
