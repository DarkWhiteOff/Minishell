/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:12:07 by tzizi             #+#    #+#             */
/*   Updated: 2024/12/20 15:07:14 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_opening_outfile(char *file, int append)
{
	int	fd;

	fd = -1;
	if (append)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
			return (-1);
		if (access(file, W_OK) != 0)
		{
			close(fd);
			return (-1);
		}
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			return (-1);
		if (access(file, W_OK) != 0)
		{
			close(fd);
			return (-1);
		}
	}
	return (fd);
}

int	handle_opening_infile(char *file, int append)
{
	int	fd;

	fd = -1;
	if (append)
	{
		return (-1);
	}
	else
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (access(file, R_OK) != 0)
		{
			close(fd);
			return (-1);
		}
	}
	return (fd);
}

int	get_fd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "|") != 0)
	{
		if (ft_strcmp(cmd[i], ">>") == 0)
		{
			if (cmd[i + 1])
				return (handle_opening_outfile(cmd[i + 1], 1));
			return (-1);
		}
		if (ft_strcmp(cmd[i], ">") == 0)
		{
			if (cmd[i + 1])
				return (handle_opening_outfile(cmd[i + 1], 0));
			return (-1);
		}
		if (ft_strcmp(cmd[i], "<") == 0)
		{
			if (cmd[i + 1])
				return (handle_opening_infile(cmd[i + 1], 0));
			return (-1);
		}
		i++;
	}
	return (1);
}

int get_cmd_number(t_main *main, char **split)
{
    int i;
    int j;
    int cmd;

    cmd = 0;
    i = 0;
    while (split[i])
    {
        if (is_cmd(split[i], main->path))
        {
            cmd++;
            j = i + 1;
            while (split[j])
            {
                if (ft_strcmp(split[j], "|") == 0)
                    break ;
                if (main->tokens[j].type == command)
                    main->tokens[j].type = argument;
                j++;
            }
            i += (j - i - 1);
        }
        i++;
    }
    return (cmd);
}
