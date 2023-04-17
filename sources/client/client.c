/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:59:14 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 15:31:17 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

static int	g_good;

void	print_and_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

void	send_char(pid_t server_pid, char c)
{
	int	width;
	int	ret;
	int	timeout;

	width = 128;
	while (width)
	{
		timeout = 0;
		usleep(50);
		ret = kill(server_pid, SIGUSR1 + (c & width) / width);
		if (ret < 0)
			print_and_exit(ERR"Can't connect to the server.");
		while (!g_good)
		{
			if (timeout++ > 3)
				print_and_exit(ERR"Server timed out.");
			sleep(1);
		}
		g_good = 0;
		width >>= 1;
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		g_good = 1;
	(void)sig;
	return ;
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	int		i;

	if (argc != 3 || ft_strlen(argv[2]) <= 0 || is_only_digits(argv[1]))
		print_and_exit(ERR"Usage: ./client <pid> <text>");
	server_pid = ft_atoi(argv[1]);
	signal(SIGUSR1, sig_handler);
	i = 0;
	send_char(server_pid, '\n');
	while (i != (int) ft_strlen(argv[2]) + 1)
	{
		send_char(server_pid, argv[2][i]);
		i++;
	}
	return (0);
}
