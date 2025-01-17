/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:34:30 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:50:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_len(char *str, char c)
{
	size_t	i;

	i = 0;
	while (*str != c && *str)
	{
		i++;
		str++;
	}
	return (i);
}

static void	*add_word_to_node(const char *str, size_t s_len,
				t_list **prev, t_list **head)
{
	t_list			*new;

	if (!*prev)
	{
		new = ft_lstnew(ft_strsub(str, 0, s_len), s_len + 1);
		if (!new)
			return (NULL);
		*head = new;
		*prev = *head;
	}
	else
	{
		new = ft_lstnew(ft_strsub(str, 0, s_len), s_len + 1);
		if (!new)
			return (NULL);
		(*prev)->next = new;
		*prev = new;
	}
	return ((void *)(1));
}

/*
** Allocates (with malloc(3)) and returns a t_list of “fresh”
** strings (all ending with ’\0’) obtained by spliting s using the
** character c as a delimiter. If the allocation fails the function returns
** NULL.
*/

t_list	*ft_strsplit_lst(char const *str, char c)
{
	t_list			*prev;
	t_list			*head;
	size_t			s_len;

	if (!str)
		return (NULL);
	head = NULL;
	prev = NULL;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str != c && *str)
		{
			s_len = word_len((char *)str, c);
			if (add_word_to_node(str, s_len, &prev, &head) == NULL)
				return (NULL);
			str += s_len;
		}
	}
	return (head);
}
