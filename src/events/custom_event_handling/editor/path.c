/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 02:47:27 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 02:54:25 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		handle_editor_patrol_slot_increment(t_doom3d *app)
{
	if (app->editor.patrol_slot < MAX_PATROL_NODES)
	{
		app->editor.patrol_slot++;
		app->editor.is_placing = false;
		doom3d_notification_add(app, (t_notification){
			.message = "Patrol Slot Incremented!",
			.type = notification_type_info, .time = 2000});
		ft_printf("Patrol slot %d\n", app->editor.patrol_slot);
	}
	else
	{
		doom3d_notification_add(app, (t_notification){
			.message = "Patrol Max Reached. Can't add more!",
			.type = notification_type_info, .time = 2000});
	}
}

void		handle_editor_patrol_slot_decrement(t_doom3d *app)
{
	if (app->editor.patrol_slot > 0)
	{
		app->editor.patrol_slot--;
		doom3d_notification_add(app, (t_notification){
			.message = "Patrol Slot Decremented!",
			.type = notification_type_info, .time = 2000});
		ft_printf("Patrol slot %d\n", app->editor.patrol_slot);
	}
	else
	{
		doom3d_notification_add(app, (t_notification){
			.message = "Patrol Slot already at zero",
			.type = notification_type_info, .time = 2000});
	}
}
