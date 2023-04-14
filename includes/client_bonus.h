/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 13:58:33 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/14 18:41:47 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_BONUS_H
# define CLIENT_BONUS_H

# define ERR "\033[0;31m[!]\033[0m "
# define OK "\033[0;32m[*]\033[0m "

# include "../libft/includes/libft.h"
# include <signal.h>
# include <sys/types.h>

int		is_only_digits(char *str);

#endif