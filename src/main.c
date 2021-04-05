/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 16:09:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

int32_t		main(void)
{
	t_doom3d	app;

	LOG_INFO("Start Doom App");
	ft_memset(&app, 0, sizeof(t_doom3d));
	srand(time(NULL));
	doom3d_run(&app);
	return (EXIT_SUCCESS);
}
