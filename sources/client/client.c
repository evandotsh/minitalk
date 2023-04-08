/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:59:14 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/08 18:16:11 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

void	send_char(pid_t server_pid, char c)
{
	int	i;

	i = 7;
	printf("\nSending %c: ", c);
	while (i >= 0)
	{
		if (c & (1 << i))
		{
			kill(server_pid, SIGUSR2);
			printf("1");
			usleep(50);
		}
		else
		{
			kill(server_pid, SIGUSR1);
			printf("0");
			usleep(50);
		}
		--i;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	int		i;

	(void) argc;
	server_pid = ft_atoi(argv[1]);
	printf("Communicating with %d...", server_pid);
	i = 0;
	while (argv[2][i] != '\0')
	{
		send_char(server_pid, argv[2][i]);
		i++;
	}
	return (0);
}
