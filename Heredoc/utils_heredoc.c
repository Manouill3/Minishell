/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:51:02 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/05 15:11:04 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_valid_char(char *buffer)
{
	int	i;
	int	j;
	char *res;

	i = 0;
	j = 0;
	res = ft_calloc(100, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (res[i] && buffer[j])
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

char	*ft_get_name(void)
{
    char    *valid_name;	
	char	buffer[1000];
	int		fd;
	int		bytes;
	
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes = read(fd, buffer, 1000);
	if (bytes == -1)
		return (NULL);
	valid_name = get_valid_char(buffer);
	if (access(valid_name, F_OK))
	{
		close(fd);
		return(valid_name);
	}
	close (fd);
	return (ft_get_name());
}