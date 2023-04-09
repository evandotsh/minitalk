/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:58:33 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/09 16:12:46 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <signal.h>
# include <sys/types.h>
# include <stdio.h>
# include <unistd.h>

int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);

#endif