/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:16:45 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/08 14:05:03 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	projectile_data_init(t_doom3d *app)
{
	app->projectile_data[projectile_type_rpg] = projectile_data_rpg(app);
	app->projectile_data[projectile_type_fireball] =
											projectile_data_fireball(app);
	app->projectile_data[projectile_type_fireball_green] =
		projectile_data_fireball_custom(app, projectile_type_fireball_green);
	app->projectile_data[projectile_type_fireball_lgreen] =
		projectile_data_fireball_custom(app, projectile_type_fireball_lgreen);
	app->projectile_data[projectile_type_fireball_pink] =
		projectile_data_fireball_custom(app, projectile_type_fireball_pink);
	app->projectile_data[projectile_type_fireball_yellow] =
		projectile_data_fireball_custom(app, projectile_type_fireball_yellow);
	app->projectile_data[projectile_type_fireball_purple] =
		projectile_data_fireball_custom(app, projectile_type_fireball_purple);
}
