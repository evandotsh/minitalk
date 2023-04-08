/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:57:32 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/08 15:59:42 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

void	handle_signal(int sig)
{
	if (sig == SIGUSR1)
		printf("0");
	else if (sig == SIGUSR2)
		printf("1");
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	printf("Hello my pid is %d!", pid);
	signal(SIGUSR1, handle_signal);
	while (1)
		sleep(1);
	return (0);
}
