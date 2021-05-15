/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 20:25:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** To load assets as a developer for the first map (FIRST_LEVEL),
** run ./doom-nukem --load_assets
** If you don't run doom with that mode, FIRST_LEVEL is required for the app
** to run.
*/

int32_t	main(int argc, char **argv)
{
	t_doom3d	app;
	int32_t		fd;
	char		level1[128];

	ft_memset(&app, 0, sizeof(t_doom3d));
	srand(time(NULL));
	if (argc == 1 && ft_strequ(argv[1], "--load_assets"))
	{
		LOG_INFO("Start Doom in Asset Load mode, dont forget to save %s,"
			" which will contain shared assets",
			FIRST_LEVEL);
		app.is_asset_load = true;
	}
	else
	{
		LOG_INFO("Start Doom App");
		ft_sprintf(level1, "assets/map_data/%s", FIRST_LEVEL);
		fd = open(level1, O_RDONLY);
		error_check(fd == -1, "Level1 not found. "
			"Level1 is needed for doom-nukem to run."
			" Create level1 with ./doom-nukem --load_assets");
		close(fd);
	}
	doom3d_run(&app);
	return (EXIT_SUCCESS);
}
