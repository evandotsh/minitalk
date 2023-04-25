/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:00:29 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/24 18:01:37 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
	* Reallocates the given memory block using malloc and free.
	*
	* @param ptr The memory block to reallocate.
	* @param new_size The new size for the memory block.
	* @return The reallocated memory block.
*/
void	*ft_realloc(void *ptr, size_t new_size)
{
	char	*new_ptr;
	size_t	cur_size;

	if (ptr == 0)
		return (malloc(new_size));
	cur_size = sizeof(ptr);
	if (new_size <= cur_size)
		return (ptr);
	new_ptr = malloc(new_size);
	ft_memcpy(ptr, new_ptr, cur_size);
	free(ptr);
	return (new_ptr);
}
