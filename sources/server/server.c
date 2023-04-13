/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:57:32 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/13 16:40:28 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

void	handle_signal(int sig, siginfo_t *info, void *ctx)
{
	static char	c;
	static int	width;

	printf("received bit\n");
	c = '\0';
	width = 128;
	(void)ctx;
	(void)info;
	c = c | (width * (sig - SIGUSR1));
	width >>= 1;
	if (width == 0)
	{
		if (!c)
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		c = '\0';
		width = 128;
	}
	kill(info->si_pid, SIGUSR1);
	usleep(30);
}

int	main(void)
{
	struct sigaction	sg_action;

	sg_action.sa_sigaction = handle_signal;
	sg_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sg_action, NULL);
	sigaction(SIGUSR2, &sg_action, NULL);
	printf("Server is up and listening (PID: %d)\n", getpid());
	while (1)
		;
	return (0);
}
