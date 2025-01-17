/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:05:38 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 17:02:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Saves the line by copying a length of next new line from remainder
** And scrolls remainder variable by that amount onwards.
*/

static void	save_line_and_scroll(char **remainder,
				char **line, int scroll_len)
{
	char	*tmp;

	*line = ft_strsub(*remainder, 0, scroll_len);
	tmp = ft_strdup(*remainder + scroll_len + 1);
	ft_strdel(remainder);
	*remainder = tmp;
}

/*
** Returns the new line & return value while finding next newline
** or end of file
*/

static int	ret_new_line(char **remainder, char **line, int ret)
{
	size_t		len;

	if (ret < 0)
		return (-1);
	else if (ret == 0 && (*remainder == NULL || (*remainder)[0] == '\0'))
		return (0);
	len = 0;
	while ((*remainder)[len] != '\0' && (*remainder)[len] != '\n')
		len++;
	if ((*remainder)[len] == '\n')
		save_line_and_scroll(remainder, line, len);
	else if ((*remainder)[len] == '\0')
	{
		*line = ft_strdup(*remainder);
		ft_strdel(remainder);
	}
	return (1);
}

/*
** Appends buffer to remainder variable to be used to read lines
** from when file pointer is further due to having already read the lines
*/

static void	append_to_remainder(char **remainder, char *buf)
{
	char	*tmp;

	if (*remainder == NULL)
		*remainder = ft_strnew(1);
	tmp = ft_strjoin(*remainder, buf);
	ft_strdel(remainder);
	*remainder = tmp;
}

/*
** A function that saves a line read from a file descriptor. The next
** call of this function will save the next line from that file.
*/

int	get_next_line(const int fd, char **line)
{
	int					ret;
	char				buf[BUFF_SIZE + 1];
	static char			*remainders[MAX_FD];

	if (fd < 0 || line == NULL || fd > MAX_FD)
		return (-1);
	if (remainders[fd] && ft_strchr(remainders[fd], '\n'))
		return (ret_new_line(&(remainders[fd]), line, 1));
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		append_to_remainder(&(remainders[fd]), buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (ret_new_line(&(remainders[fd]), line, ret));
}
