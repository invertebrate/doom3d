/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:11:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/28 14:59:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RADIX_SORT_H
# define RADIX_SORT_H

# include "libft.h"

/*
** Dont change
*/
# define RADIXBITS 8
# define RADIXTOTALBITS 32

/*
** RADIX = 1 << RADIXTOTALBITS(8) = 256
*/
# define RADIX 256
# define HISTOLEN RADIX
# define EXPECTED_THREADS 8

typedef struct	s_radix_params
{
	size_t		work_index;
	uint32_t	*arr_keys;
	uint32_t	*out_keys;
	uint32_t	*arr_vals;
	uint32_t	*out_vals;
	size_t		shift;
	size_t		bucket_size;
	size_t		count[HISTOLEN];
	size_t		index[HISTOLEN];
	t_bool		is_key_val;
}				t_radix_params;

void			radix_sort(t_thread_pool *pool, uint32_t *array,
					size_t size);
void			radix_sort_key_val(t_thread_pool *pool,
					uint32_t *key_vals[2], size_t size);

#endif
