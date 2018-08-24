/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rejocic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 14:18:56 by rejocic           #+#    #+#             */
/*   Updated: 2018/08/24 13:26:50 by rejocic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		res_start(char **res, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*res)[i] && (*res)[i] != '\n')
		i++;
	if ((*res)[i] == '\n')
	{
		(*res)[i] = '\0';
		*line = ft_strdup(*res);
		tmp = *res;
		*res = ft_strdup((*res) + (i + 1));
		free(tmp);
		return (1);
	}
	return (0);
}

int		res_end(char **res, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*res)[i] && (*res)[i] != '\n')
		i++;
	if ((*res)[i] == '\n')
	{
		(*res)[i] = '\0';
		*line = ft_strdup(*res);
		tmp = *res;
		*res = ft_strdup((*res) + (i + 1));
		free(tmp);
		return (1);
	}
	else
	{
		*line = *res;
		*res = ft_strnew(0);
		return (1);
	}
}

int		readfunc(char **res, char **line, char *str, int r)
{
	int		i;
	char	*tmp;

	i = 0;
	(str)[r] = '\0';
	while ((str)[i] != '\n' && i < r)
		i++;
	if ((str)[i] == '\n')
	{
		(str)[i] = '\0';
		*line = ft_strjoin(*res, str);
		tmp = *res;
		*res = ft_strdup((str) + (i + 1));
		free(tmp);
		return (1);
	}
	else
	{
		tmp = *res;
		*res = ft_strjoin(*res, str);
		free(tmp);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int			r;
	char		str[BUFF_SIZE + 1];
	static char	*res[MAX_FD];

	if (fd < 0)
		return (-1);
	if (res[fd] == NULL)
		res[fd] = ft_strnew(0);
	if (res[fd] != '\0')
		if ((res_start(&res[fd], line)) == 1)
			return (1);
	while ((r = read(fd, str, BUFF_SIZE)) > 0)
		if ((readfunc(&res[fd], line, str, r)) == 1)
			return (1);
	if (r == 0 && res[fd][r] != '\0')
		return (res_end(&res[fd], line));
	if (r < 0)
		return (-1);
	return (0);
}
