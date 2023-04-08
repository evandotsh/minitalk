/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:59:14 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/08 17:45:46 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

void	send_char(pid_t server_pid, char c)
{
	int	i;

	(void) server_pid;
	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		--i;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	int		i;

	(void) argc;
	i = 0;
	server_pid = 20983;
	while (argv[1][i] != '\0')
	{
		send_char(server_pid, argv[1][i]);
		i++;
	}
	return (0);
}
