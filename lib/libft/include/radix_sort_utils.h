/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 00:55:48 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 14:43:20 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RADIX_SORT_UTILS_H
# define RADIX_SORT_UTILS_H

# include "radix_sort.h"

/*
** Radix utils
*/

void			pad_array_key_val(uint32_t *key_vals[2],
					size_t size, size_t padded_size);
void			pad_array(uint32_t *array, size_t size, size_t padded_size);
void			copy_array(uint32_t *dst, uint32_t *src,
					size_t arrays_size);
void			copy_array_key_vals(uint32_t *dst[2], uint32_t *src[2],
					size_t arrays_size);
void			init_params(t_radix_params *thread_params, size_t padded_size,
					t_bool is_key_val);

/*
** Radix work
*/

void			reorder(t_thread_pool *pool,
					t_radix_params *thread_params,
					size_t shift_pass,
					uint32_t *arrays[4]);
void			prefix_sum(t_radix_params *thread_params);
void			histogram(t_thread_pool *pool,
					t_radix_params *thread_params,
					size_t shift_pass,
					uint32_t *arrays[4]);
void			histogram_and_local_reorder(void *args);
void			reorder_work(void *args);

#endif
