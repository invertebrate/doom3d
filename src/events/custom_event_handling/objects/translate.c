/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 01:29:03 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 14:25:17 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_object_translate_x(t_doom3d *app, t_3d_object *object,
					int32_t amount)
{
	(void)app;
	l3d_3d_object_translate(object, amount, 0, 0);
}

void	handle_object_translate_y(t_doom3d *app, t_3d_object *object,
					int32_t amount)
{
	(void)app;
	l3d_3d_object_translate(object, 0, amount, 0);
}

void	handle_object_translate_z(t_doom3d *app, t_3d_object *object,
					int32_t amount)
{
	(void)app;
	l3d_3d_object_translate(object, 0, 0, amount);
}
