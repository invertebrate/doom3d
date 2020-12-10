/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_tests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:17:48 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/19 15:40:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oh_test.h"
#include "libft.h"

const char		*test_ft_memset(void)
{
	char			buf[16];

	ft_memset(buf, 0, 16);
	ft_memset(buf, 'c', 11);
	OH_ASSERT("ftMemset didnt work", ft_strequ(buf, "ccccccccccc\0"));
	ft_memset(buf, 'o', 12);
	buf[12] = '\0';
	OH_ASSERT("ftMemset didnt work", ft_strequ(buf, "oooooooooooo\0"));
	return (0);
}

const char		*test_ft_memset_ints(void)
{
	uint32_t			nb;

	nb = 256;
	ft_memset(&nb, 255, sizeof(nb));
	OH_ASSERT("ftMemset didnt work for int32", nb == 0xFFFFFFFF);
	return (0);
}
