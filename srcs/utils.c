/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:31:14 by jihoh             #+#    #+#             */
/*   Updated: 2022/07/23 17:38:27 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	put_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

void	*ft_malloc(unsigned int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		exit(put_error("error: malloc failed\n"));
	return (ptr);
}
