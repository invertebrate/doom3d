/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:14:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 16:14:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			doom3d_notifications_update(t_doom3d *app)
{
	t_notification	*last_notification;
	t_list			**last_node;

	last_node = &app->notifications;
	if (!*last_node)
		return ;
	while ((*last_node)->next)
		last_node = &(*last_node)->next;
	last_notification = (*last_node)->content;
	last_notification->time -= app->info.delta_time;
	if (last_notification->time <= 0)
	{
		free(last_notification);
		free(*last_node);
		*last_node = NULL;
	}
}

void			doom3d_notification_add(t_doom3d *app,
					t_notification notification)
{
	if (app->notifications == NULL)
		app->notifications = ft_lstnew(&notification, sizeof(t_notification));
	else
		ft_lstadd(&app->notifications,
			ft_lstnew(&notification, sizeof(t_notification)));
}

void			doom3d_notifications_delete_all(t_doom3d *app)
{
	t_list		*node;
	t_list		*tmp;

	node = app->notifications;
	while (node)
	{
		tmp = node;
		free((t_notification*)node->content);
		node = node->next;
		free(tmp);
	}
	app->notifications = NULL;
}
