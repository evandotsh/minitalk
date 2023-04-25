/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:57:32 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/25 14:13:07 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server_bonus.h"

void	reset_session(pid_t new_pid, pid_t *old_pid, int *bit, int *c)
{
	*old_pid = new_pid;
	*bit = 0;
	*c = 255;
}

static void	stash_char(char c)
{
	static char	*str;
	char		*tmp;

	if (!str)
	{
		str = malloc(1);
		str[0] = '\0';
	}
	tmp = malloc(2);
	tmp[0] = c;
	tmp[1] = '\0';
	str = ft_strjoin(str, tmp);
	if (c == 0)
	{
		ft_printf("%s\n", str);
		free(str);
		str = NULL;
	}
	free(tmp);
}

void	handle_signal(int sig, siginfo_t *info, void *ctx)
{
	static int		c;
	static int		bit;
	static pid_t	current_pid;

	(void) ctx;
	if (!c || current_pid != info->si_pid)
		reset_session(info->si_pid, &current_pid, &bit, &c);
	if (sig == SIGUSR1)
		c ^= (128 >> bit);
	else if (sig == SIGUSR2)
		c |= (128 >> bit);
	bit++;
	if (bit == 8)
	{
		stash_char(c);
		if (c == 0)
			kill(current_pid, SIGUSR2);
		c = 255;
		bit = 0;
	}
	usleep(100);
	kill(current_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sg_action;

	sigemptyset(&sg_action.sa_mask);
	sg_action.sa_sigaction = handle_signal;
	sg_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sg_action, NULL);
	sigaction(SIGUSR2, &sg_action, NULL);
	ft_putstr_fd(OK"Server is up and listening on PID ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
