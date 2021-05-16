/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 22:10:50 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/16 20:23:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	write_assets(int32_t fd, t_doom3d *app)
{
	(void)fd;
	LOG_WARN("Assets size: %llu", get_assets_size(&app->assets));
}
