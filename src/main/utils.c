/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:45:37 by wshoweky          #+#    #+#             */
/*   Updated: 2025/09/08 11:37:42 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	error_return(char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	return (ERROR);
}

void	error_exit(char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

int	free_and_close(int fd, char *line, char *msg)
{
	if (line)
		free(line);
	if (fd)
		close(fd);
	return (error_return(msg));
}

int	ft_isdigit_hex(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F'));
}
