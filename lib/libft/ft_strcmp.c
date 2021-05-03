/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:08:21 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:42:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_strcmp() and ft_strcmp() functions lexicographically
** compare the null-terminated strings s1 and s2.
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (!*s1 && !*s2)
		return (0);
	else if (*s1 && !*s2)
		return (1);
	if ((unsigned char)*s1 < (unsigned char)*s2)
		return (-1);
	return (1);
}
