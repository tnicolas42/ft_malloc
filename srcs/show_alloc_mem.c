/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 14:03:02 by tnicolas          #+#    #+#             */
/*   Updated: 2018/05/31 17:41:31 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | show_alloc_mem.c                                         |
**   |     print_alloc(22 lines)                                |
**   |     show_alloc_mem(17 lines)                             |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include <ft_malloc.h>

static int	print_alloc(void *ptr, size_t *total_octet)
{
	int		i;
	size_t	nb_octet;

	nb_octet = 0;
	i = 0;
	while (ptr)
	{
		if (((t_info*)ptr)->free == false)
		{
			i++;
			nb_octet += ((t_info*)ptr)->official_size;
			ft_printf("\t%p - %p : "BOLD"%d"EOC" octets\n", ptr + sizeof(t_info),
					ptr + sizeof(t_info) + ((t_info*)ptr)->official_size,
					((t_info*)ptr)->official_size);
		}
		ptr = ((t_info*)ptr)->next;
	}
	if (i > 0)
		ft_printf(YELLOW""BOLD"\ttotal:"EOC""BOLD" %d"EOC" block ("BOLD"%zu"EOC
				" octets)\n"EOC, i, nb_octet);
	*total_octet += nb_octet;
	return (i);
}

void		show_alloc_mem(void)
{
	void	*ptr;
	int		total;
	size_t	total_octet;

	total_octet = 0;
	total = 0;
	ft_printf(YELLOW""BOLD"TINY:"EOC""BOLD" %p\n"EOC, data->ptr_tiny);
	ptr = data->ptr_tiny;
	total += print_alloc(ptr, &total_octet);
	ft_printf(YELLOW""BOLD"SMALL:"EOC""BOLD" %p\n"EOC, data->ptr_small);
	ptr = data->ptr_small;
	total += print_alloc(ptr, &total_octet);
	ft_printf(YELLOW""BOLD"LARGE:"EOC""BOLD" %p\n"EOC, data->ptr_large);
	ptr = data->ptr_large;
	total += print_alloc(ptr, &total_octet);
	ft_printf(YELLOW""BOLD"total:"EOC""BOLD" %d"EOC" block ("BOLD"%zu"EOC
			" octets)\n"EOC, total, total_octet);
}
