/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:15:59 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 19:33:48 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		settings_init(t_doom3d *app)
{
	app->settings.is_normal_map = false;
	app->settings.is_skybox = true;
	app->settings.width = 960;
	app->settings.height = 540;
	app->is_third_person = false;
}
