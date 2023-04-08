/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:57:32 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/08 19:03:05 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.h"

static int	g_cur_bit;

char	binarytochar(int bits[])
{
	char	c;
	int		i;

	i = 0;
	c = 0;
	while (i < 8)
	{
		c |= bits[i] << (7 - i);
		i++;
	}
	return (c);
}

char	reconstruct(int bit)
{
	static int	array[7];

	if (g_cur_bit >= 7)
	{
		array[g_cur_bit] = bit;
		g_cur_bit = 0;
		return (binarytochar(array));
	}
	array[g_cur_bit] = bit;
	g_cur_bit++;
	return (0);
}

void	handle_signal(int sig)
{
	char	c;

	c = 0;
	if (sig == SIGUSR1)
		c = reconstruct(0);
	else if (sig == SIGUSR2)
		c = reconstruct(1);
	if (c != 0)
		write(1, &c, 1);
}

int	main(void)
{
	g_cur_bit = 0;
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		usleep(100);
	return (0);
}
