/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:59:14 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/13 16:39:53 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

void	send_char(pid_t server_pid, char c)
{
	int	width;

	width = 128;
	while (width)
	{
		kill(server_pid, SIGUSR1 + (c & width) / width);
		printf("sent bit\n");
		width >>= 1;
	}
}

void	sig_handler(int sig)
{
	printf("received ack, continuing...\n");
	(void)sig;
	return ;
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	int		i;

	(void)argc;
	server_pid = ft_atoi(argv[1]);
	signal(SIGUSR1, sig_handler);
	printf("Communicating with %d...", server_pid);
	i = 0;
	while (argv[2][i] != '\0')
	{
		send_char(server_pid, argv[2][i]);
		i++;
	}
	return (0);
}
