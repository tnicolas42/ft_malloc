/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 13:34:53 by tnicolas          #+#    #+#             */
/*   Updated: 2018/05/31 13:57:47 by tnicolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   ____________________________________________________________
**   | free.c                                                   |
**   |     free(15 lines)                                       |
**   ------------------------------------------------------------
**           __n__n__  /
**    .------`-\00/-'/
**   /  ##  ## (oo)
**  / \## __   ./
**     |//YY \|/
**     |||   |||
*/

#include <ft_malloc.h>

void		free_large(void *ptr, enum e_type_alloc type, t_info *info)
{
	(void)ptr;
	if (info->prev)
		info->prev->next = info->next;
	if (info->next)
		info->next->prev = info->prev;
	munmap(info, info->size + sizeof(info));
}

void		free_little(void *ptr, enum e_type_alloc type, t_info *info)
{
	(void)ptr;
	info->free = true;
	if (info->prev && info->first_in_block == false)
	{
		if (info->prev->free == true)
		{
			info->prev->size += info->size + sizeof(t_info);
			info->prev->next = info->next;
			if (info->next)
				info->next->prev = info->prev;
			info = info->prev;
		}
	}
	if (info->next && info->next->first_in_block == false)
	{
		if (info->next->free == true)
		{
			info->size += info->next->size + sizeof(t_info);
			if (info->next->next)
				info->next->next->prev = info;
			info->next = info->next->next;
		}
	}
	if (info->first_in_block == true)
	{
		if (info->next == NULL || info->next->first_in_block == true)
		{
			if (info->next)
				info->next->prev = info->prev;
			if (info->prev)
				info->prev->next = info->next;
			if (type == TYPE_TINY)
			{
				if (info == data->ptr_tiny)
				{
					data->ptr_tiny = info->next;
					data->size_tiny -= SIZE_MAX_TINY;
				}
				munmap(info, SIZE_MAX_TINY);
			}
			else
			{
				if (info == data->ptr_small)
				{
					data->ptr_small = info->next;
					data->size_small -= SIZE_MAX_SMALL;
				}
				munmap(info, SIZE_MAX_SMALL);
			}
		}
	}
}

void		free(void *ptr)
{
	enum e_type_alloc	type;
	t_info				*info;

	printf("fruit %s\n", ptr);
	if (!ptr)
		return ;
	info = ptr - sizeof(t_info);
	type = TYPE_LARGE;
	type = (info->size <= SIZE_MAX_SMALL) ? TYPE_SMALL : type;
	type = (info->size <= SIZE_MAX_TINY) ? TYPE_TINY : type;
	if (type == TYPE_LARGE)
		free_large(ptr, type, info);
	else
		free_little(ptr, type, info);
}
