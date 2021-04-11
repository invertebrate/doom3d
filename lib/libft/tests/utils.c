/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:57:02 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/27 21:56:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void			rand_array(uint32_t *array, uint32_t array_size)
{
	size_t	i;

	i = -1;
	while (++i < array_size)
		array[i] = rand();
}

t_bool			arrays_match(uint32_t *arr1, uint32_t *arr2,
					size_t arrays_size)
{
	size_t	i;

	i = -1;
	while (++i < arrays_size)
		if (arr1[i] != arr2[i])
			return (false);
	return (true);
}

int				check_comp(const void *a, const void *b)
{
	size_t	f;
	size_t	s;

	f = *((int32_t*)a);
	s = *((int32_t*)b);
	if (f > s)
		return (1);
	if (f < s)
		return (-1);
	return (0);
}

void			sort_check_array(uint32_t *check_array, uint32_t array_size)
{
	qsort(check_array, array_size, sizeof(*check_array), check_comp);
}
