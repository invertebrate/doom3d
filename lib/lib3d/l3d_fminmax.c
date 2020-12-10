/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_fminmax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:22:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Returns min of two float values
*/

float	l3d_fmin(float n1, float n2)
{
	return (n1 < n2 ? n1 : n2);
}

/*
** Returns max of two float values
*/

float	l3d_fmax(float n1, float n2)
{
	return (n1 > n2 ? n1 : n2);
}
