/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notification.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:08:35 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/12 08:49:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOTIFICATION_H
# define NOTIFICATION_H

# include "libft.h"

/*
** Defines what type of notifications exist which then correspond to
** how the notification gets rendered.
*/

typedef enum e_nofitication_type
{
	notification_type_info,
	notification_type_layer,
	notification_type_story,
}							t_notification_type;

/*
** Notifications that represent data info that gets displayed
** on screen to the player / user of the app.
*/

typedef struct s_notification
{
	const char				*message;
	t_notification_type		type;
	int32_t					time;
	int32_t					time_start;
}							t_notification;

#endif
