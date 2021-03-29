/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:43:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 16:50:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_editor_placement_start(t_doom3d *app)
{
	app->editor.is_placing = true;
}

void	handle_editor_placement_end(t_doom3d *app)
{
	app->editor.is_placing = false;
}

