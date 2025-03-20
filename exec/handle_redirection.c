/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:56 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/20 16:33:01 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    check_access(t_fds *fds)
{
	int i;
	
    i = 0;
	fds->fd_infile = -1;
	fds->fd_outfile = -1;
    while (fds->file_input[i])
    {	
		if (access(fds->file_input[i], R_OK | F_OK) != -1)
		{
			if (fds->fd_infile != -1)
				close(fds->fd_infile);
			fds->fd_infile = open(fds->file_input[i], O_RDONLY, 0644);
		}
        else
			perror("infile");
        i++;
    }
    i = 0;
    while (fds->file_output[i])
    {
		if (access(fds->file_output[i], F_OK | W_OK) != -1)
		{
			if (fds->fd_outfile != -1)
				close(fds->fd_outfile);
			fds->fd_outfile = open(fds->file_output[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
        else
        {
			if (access(fds->file_output[i], F_OK) == -1)
			{
				if (fds->fd_outfile != -1)
					close(fds->fd_outfile);
				fds->fd_outfile = open(fds->file_output[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
        }
        i++;
    }
}

void	ft_list_file(t_list_char *tok, t_fds *fds)
{
	t_list_char	*tmp;
	int			count_input;
	int			count_output;
	
	fds->file_input = NULL;
	fds->file_output = NULL;
	tmp = tok;
	count_input = 0;
	count_output = 0;
	while (tmp)
	{
		if (( !ft_strcmp(tmp->data, ">") || !ft_strcmp(tmp->data, ">>")) && tmp->next->data != NULL)
		count_output++;
		if (!ft_strcmp(tmp->data, "<"))
		count_input++;
		tmp = tmp->next;
	}
	fds->file_input = ft_calloc(count_input + 1, sizeof(char *));
	fds->file_output = ft_calloc(count_output + 1, sizeof(char *));
}

void    ft_check_cmd(t_list_char *tok)
{
	t_list_char *tmp;
	char *tmp_data;
	
    tmp = tok;
    while(tmp)
    {
		if (!ft_strcmp(tmp->name, "arg"))
		{
			if (!ft_strcmp(tmp->prev->data, "<") || !ft_strcmp(tmp->prev->data, ">") || !ft_strcmp(tmp->prev->data, ">>"))
			{
				if (!tmp->prev->prev || (ft_strcmp(tmp->prev->prev->name, "cmd") && ft_strcmp(tmp->prev->prev->name, "arg")))
				{
					tmp_data = ft_strjoin("/bin/", tmp->next->data);
					if (!access(tmp_data, X_OK))
						tmp->next->name = "cmd";
					free(tmp_data);
				}
			}
		}
		tmp = tmp->next;
    }
}

void    handle_redirection(t_list_char *tok, t_fds *fds)
{
	ft_check_file(tok, fds);
	ft_check_cmd(tok);
	check_access(fds);
}

void	ft_check_file(t_list_char *tok, t_fds *fds)
{
	int			i;
	int			j;
	t_list_char *tmp;

	tmp = tok;
	i = 0;
	j = 0;
	ft_list_file(tok, fds);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "arg"))
		{
			if (!ft_strcmp(tmp->prev->data, "<"))
			{
				fds->file_input[i] = tmp->data;
				i++;
			}
			if  (!ft_strcmp(tmp->prev->data, ">") || !ft_strcmp(tmp->prev->data, ">>"))
			{
				fds->file_output[j] = tmp->data;
				j++;
			}
		}
		tmp = tmp->next;
	}
}
