/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 12:09:12 by tnicolas          #+#    #+#             */
/*   Updated: 2018/05/24 12:09:12 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

void		*malloc(size_t size)
{
	void	*ptr;

	ptr = alloc_memory(size);
	return (ptr);
}
