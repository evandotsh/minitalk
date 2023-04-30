/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:59:14 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/29 15:48:44 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

static int	g_ack;

static int	is_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static void	print_and_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

static void	send_char(pid_t server_pid, char c)
{
	int	bit;
	int	ret;
	int	timeout;

	bit = 0;
	timeout = 0;
	while (bit < 8)
	{
		g_ack = 0;
		ret = kill(server_pid, SIGUSR1 + ((c & (128 >> bit)) > 0));
		if (ret < 0)
			print_and_exit(ERR "Can't connect to the server.");
		while (!g_ack)
		{
			if (timeout++ > 3)
				print_and_exit(ERR "Server timed out.");
			sleep(1);
		}
		timeout = 0;
		bit++;
		usleep(100);
	}
}

static void	sig_handler(int sig, siginfo_t *info, void *ctx)
{
	(void)ctx;
	(void)info;
	if (sig == SIGUSR1)
		g_ack = 1;
	if (sig == SIGUSR2)
		ft_printf(OK"Message received by server.\n");
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	struct sigaction	sg_action;
	int					i;
	int					len;

	if (argc != 3 || ft_strlen(argv[2]) <= 0 || is_only_digits(argv[1]))
		print_and_exit(ERR "Usage: ./client <pid> <text>");
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		print_and_exit(ERR"Invalid server pid");
	sigemptyset(&sg_action.sa_mask);
	sg_action.sa_flags = SA_SIGINFO;
	sg_action.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sg_action, NULL);
	sigaction(SIGUSR2, &sg_action, NULL);
	i = 0;
	len = ft_strlen(argv[2]);
	while (i <= len)
		send_char(server_pid, argv[2][i++]);
	return (0);
}
