/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector3_forward.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 01:07:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Get forward vector from vector3 eye looking at vector3 target
*/

void	ml_vector3_forward(t_vec3 eye, t_vec3 target, t_vec3 res)
{
	t_vec3	forward_unnormalized;

	ml_vector3_sub(target, eye, forward_unnormalized);
	ml_vector3_normalize(forward_unnormalized, res);
}
