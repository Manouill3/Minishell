/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:56 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/24 16:21:09 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    check_access_output(t_fds *fds)
{
	int i;
	
    i = 0;
	fds->fd_infile = -1;
	fds->fd_outfile = -1;
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

void    check_access_input(t_fds *fds)
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

void    ft_check_cmd(t_list_char *tok, t_list_char *env)
{
	int		i;
	t_list_char *tmp;
	char **cmd_path;
	char *tmp_data;
	char *tmp_data2;
	
    tmp = tok;
	while (ft_strncmp(env->data, "PATH=", 5))
		env = env->next;
	cmd_path = ft_normal_split(env->data + 5, ':');
    while(tmp)
    {
		if (!ft_strcmp(tmp->name, "arg"))
		{
			if (!ft_strcmp(tmp->prev->data, "<") || !ft_strcmp(tmp->prev->data, ">") || !ft_strcmp(tmp->prev->data, ">>"))
			{
				if (!tmp->prev->prev || (ft_strcmp(tmp->prev->prev->name, "cmd") || ft_strcmp(tmp->prev->prev->name, "arg")))
				{
					i = 0;
					while(cmd_path[i])
					{
						tmp_data = ft_strjoin(cmd_path[i], "/");
						tmp_data2 = ft_strjoin(tmp_data, tmp->data);
						free(tmp_data);
						printf("tmp_data = %s\n", tmp_data2);
						if (!access(tmp_data2, X_OK))
						{
							tmp->next->name = "cmd";
							free(tmp_data2);
							break;
						}
						i++;
						free(tmp_data2);
					}
				}
			}
		}
		tmp = tmp->next;
    }
	tmp = tok;
	while(tmp)
	{
		printf("name = %s\n", tmp->name);
		printf("data = %s\n", tmp->data);
		tmp = tmp->next;
	}
	ft_free_tab(cmd_path);
}

void    handle_redirection(t_list_char *tok, t_fds *fds, t_list_char *env)
{
	ft_check_file(tok, fds);
	ft_check_cmd(tok, env);
	check_access_input(fds);
	check_access_output(fds);
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
