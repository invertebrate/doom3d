/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:57:40 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/27 21:54:48 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

void			rand_array(uint32_t *array, uint32_t array_size);
t_bool			arrays_match(uint32_t *arr1, uint32_t *arr2,
					size_t arrays_size);
void			sort_check_array(uint32_t *check_array, uint32_t array_size);

#endif
