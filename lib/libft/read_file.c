/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:15:37 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 16:22:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	alloc_first(t_file_contents *contents, char *buf, int ret)
{
	contents->capacity = FILE_READ_BUF * 4;
	contents->buf = malloc(contents->capacity);
	if (contents->buf)
		ft_memcpy(contents->buf, buf, ret);
}

static t_bool	add_to_buffer(t_file_contents *contents,
					char *buf, int i, int ret)
{
	void			*tmp;

	if (i == 0)
		alloc_first(contents, buf, ret);
	else if (i == 0)
		return (false);
	else
	{
		if (contents->size + ret > contents->capacity)
		{
			tmp = contents->buf;
			contents->buf = malloc(contents->capacity * 2);
			if (!contents->buf)
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

static t_file_contents	*read_while(int fd)
{
	char			buf[FILE_READ_BUF + 1];
	int				i;
	int				ret;
	t_file_contents	*contents;

	i = 0;
	contents = malloc(sizeof(*contents));
	if (!contents)
		return (NULL);
	contents->size = 0;
	contents->capacity = 0;
	contents->buf = NULL;
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, FILE_READ_BUF);
		if (!add_to_buffer(contents, buf, i, ret))
			return (NULL);
		i++;
	}
	ft_memset(contents->buf + contents->size, 0, 1);
	return (contents);
}

t_file_contents	*read_file(const char *filename)
{
	t_file_contents	*contents;
	int				fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1
		&& ft_dprintf(2, "Failed to open file %s\n", filename))
		return (NULL);
	contents = read_while(fd);
	fd = close(fd);
	if (fd == -1
		&& ft_dprintf(2, "Failed to close file %s\n", filename))
		return (NULL);
	return (contents);
}

void	destroy_file_contents(t_file_contents *f)
{
	free(f->buf);
	free(f);
}
