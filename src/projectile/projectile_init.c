/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:16:45 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/12 21:41:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	projectile_data_init(t_doom3d *app)
{
	app->projectile_data[projectile_type_rpg] = projectile_data_rpg(app);
}