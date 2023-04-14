/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:57:32 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/14 18:57:42 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server_bonus.h"

void	reset_session(pid_t new_pid, pid_t *old_pid, int *width, char *c)
{
	*old_pid = new_pid;
	*width = 128;
	*c = 0;
}

void	handle_signal(int sig, siginfo_t *info, void *ctx)
{
	static char		c;
	static int		width;
	static pid_t	current_pid;

	(void)ctx;
	if (current_pid != info->si_pid)
		reset_session(info->si_pid, &current_pid, &width, &c);
	c = c | (width * (sig - SIGUSR1));
	width >>= 1;
	if (!width)
	{
		if (c == '\0')
			kill(info->si_pid, SIGUSR2);
		if (c)
			write(1, &c, 1);
		c = 0;
		width = 128;
	}
	usleep(50);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sg_action;

	sg_action.sa_sigaction = handle_signal;
	sg_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sg_action, NULL);
	sigaction(SIGUSR2, &sg_action, NULL);
	ft_putstr_fd(OK"Server is up and listening on PID ", 1);
	ft_putnbr_fd(getpid(), 1);
	while (1)
		;
	return (0);
}
