/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_rand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:26:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Just a simple random number between 0.0 and 1.0
*/
double			l3d_rand_d(void)
{
	return ((double)rand() / RAND_MAX);
}

/*
** Random unsigned int (used in e.g. object ids and object retrievals in
** runtime)
*/
uint32_t		l3d_random_uuid(void)
{
	return (rand());
}
