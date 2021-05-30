/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtitles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:03:43 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/30 19:47:29 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	set_subtitles_0_to_10(const char *subtitles[20])
{
	subtitles[0] = "Office lady: "
		"Johnson, the research center has gone dark.\n"
		"Go find out what's going on.\n                    ";
	subtitles[1] = "Johnson: The door is jammed.\n"
		"Office lady: I am reading through the blueprints."
		"There seems to be a way around through the caverns."
		"\n                    ";
	subtitles[2] = "Johnson: Hmmm. I need to find a key."
		"\n                    ";
	subtitles[3] = "Johnson: Fuck. That's a big boy.\n                    ";
	subtitles[4] = "Johnson: Fuck. That's a big boy.\n                    ";
	subtitles[5] = "Office lady: I am reading elevated temperature from your"
		"suit.\nRemember, your suit can only handle 200 degrees."
		"\n                    ";
	subtitles[6] = "Johnson: Fuck. That's hotter than sauna.\n"
		"I don't want to fall down there.\n                    ";
	subtitles[7] = "Office lady: You need to go upstairs to find the super "
		"computers.\nThey should shed some light on what happened."
		"\n                    ";
	subtitles[8] = "Johnson: Fuck. I hate elevators.\n                    ";
	subtitles[9] = "Office lady: Oh no! They've awakened an ancient demon "
		"deeper in the cave.\nYou must go kill it before it lays eggs!"
		"\n                    ";
	subtitles[10] = "Johnson: Fuck. I hate being pest control all the time.\n"
		"I need a raise.\n                    ";
}

static void	set_subtitles_10_to_20(const char *subtitles[20])
{
	subtitles[11] = "Office lady: Arrays of what?\n                    ";
	subtitles[12] = "Johnson: Fuck you, you know what I meant."
		"\n                    ";
	subtitles[13] = "Johnson: Fuck. This looks less healthy than 2020."
		"\n                    ";
	subtitles[14] = "Office lady: Your suit should protect you from the toxic "
		"environment\nas long as you don't expose yourself for too long."
		"\n                    ";
	subtitles[15] = "Johnson: Fuck. That's nasty.\n"
		"I don't want to fall down there.\n                    ";
	subtitles[16] = "Johnson: Fuck.\n                    ";
	subtitles[17] = "Johnson: It's time to kick ass and chew bubblegum."
		"Office lady: Bubblegum?"
		" How can you eat bubblegum with your suit on?\n                    ";
	subtitles[18] = "Johnson: Eat shit and die.\n                    ";
	subtitles[19] = "Office lady: Congratulations Johnson! "
		"You defeated the ancient demon and saved us all!\n"
		"Will you make it back in time for coffee?"
		"\n                    ";
}

const char	*get_subtitle_by_log_id(int32_t log_id)
{
	const char	*subtitles[20];
	int32_t		i;

	set_subtitles_0_to_10(subtitles);
	set_subtitles_10_to_20(subtitles);
	i = log_id - sf_audio_log_1;
	return (subtitles[i]);
}

void	show_subtitle(t_doom3d *app, int32_t log_id)
{
	const char	*subtitle;

	subtitle = get_subtitle_by_log_id(log_id);
	notify_user(app, (t_notification){
		.message = subtitle, .type = notification_type_story});
}
