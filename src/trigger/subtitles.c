/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtitles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:03:43 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/12 10:11:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	set_subtitles_10_to_20(const char *subtitles[20])
{
	subtitles[10] = "Something\n  ";
	subtitles[11] = "Something\n  ";
	subtitles[12] = "Something\n  ";
	subtitles[13] = "Something\n  ";
	subtitles[14] = "Something\n  ";
	subtitles[15] = "Something\n  ";
	subtitles[16] = "Something\n  ";
	subtitles[17] = "Something\n  ";
	subtitles[18] = "Something\n  ";
	subtitles[19] = "Something\n  ";
}

const char	*get_subtitle_by_log_id(int32_t log_id)
{
	const char	*subtitles[20];
	int32_t		i;

	subtitles[0] = "Something\n  ";
	subtitles[1] = "Something\n  ";
	subtitles[2] = "Something\n  ";
	subtitles[3] = "Something\n  ";
	subtitles[4] = "Something\n  ";
	subtitles[5] = "Something\n  ";
	subtitles[6] = "Something\n  ";
	subtitles[7] = "Something\n  ";
	subtitles[8] = "Something\n  ";
	subtitles[9] = "Something\n  ";
	set_subtitles_10_to_20(subtitles);
	i = log_id - sf_audio_log_1;
	return (subtitles[i]);
}
