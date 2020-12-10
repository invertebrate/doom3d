/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:15:37 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:15:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_bool				add_to_buffer(t_file_contents *contents,
							char *buf, int i, int ret)
{
	void			*tmp;

	if (i == 0)
	{
		contents->capacity = FILE_READ_BUF * 4;
		if ((contents->buf = malloc(contents->capacity)))
			ft_memcpy(contents->buf, buf, ret);
	}
	else if (i == 0)
		return (false);
	else
	{
		if (contents->size + ret > contents->capacity)
		{
			tmp = contents->buf;
			if (!((contents->buf = malloc(contents->capacity * 2))))
				return (false);
			contents->capacity *= 2;
			ft_memcpy(contents->buf, tmp, contents->size);
			free(tmp);
		}
		ft_memcpy(contents->buf + contents->size, buf, ret);
	}
	contents->size += ret;
	return (true);
}

static t_file_contents		*read_while(int fd)
{
	char			buf[FILE_READ_BUF + 1];
	int				i;
	int				ret;
	t_file_contents	*contents;

	i = 0;
	if (!(contents = malloc(sizeof(*contents))))
		return (NULL);
	contents->size = 0;
	contents->capacity = 0;
	contents->buf = NULL;
	while ((ret = read(fd, buf, FILE_READ_BUF)) > 0)
	{
		if (!add_to_buffer(contents, buf, i, ret))
			return (NULL);
		i++;
	}
	ft_memset(contents->buf + contents->size, 0, 1);
	return (contents);
}

t_file_contents				*read_file(const char *filename)
{
	t_file_contents	*contents;
	int				fd;

	if ((fd = open(filename, O_RDONLY)) == -1 &&
		ft_dprintf(2, "Failed to open file %s\n", filename))
		return (NULL);
	contents = read_while(fd);
	if ((fd = close(fd)) == -1 &&
		ft_dprintf(2, "Failed to close file %s\n", filename))
		return (NULL);
	return (contents);
}

void						destroy_file_contents(t_file_contents *f)
{
	free(f->buf);
	free(f);
}
