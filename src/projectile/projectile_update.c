/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:53:38 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 18:36:12 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	projectile_update(t_doom3d *app, t_3d_object *obj)
{
	t_projectile	*projectile;
	t_vec3			pos_new;
//	t_vec3			dir_new;

	projectile = obj->params;
	//ml_vector3_mul(projectile->dir, projectile->speed, dir_new);
	ml_vector3_add(obj->position, projectile->dir, pos_new);
	ml_vector3_copy(pos_new, obj->position);
	l3d_3d_object_translate(obj, projectile->dir[0], projectile->dir[1], projectile->dir[2]);
	projectile->traveled += projectile->speed;
	if (projectile->traveled > projectile->range)
	{
		object_set_for_deletion(app, obj);
		ft_printf("Deleted projectile! \n"); //test
	}
}