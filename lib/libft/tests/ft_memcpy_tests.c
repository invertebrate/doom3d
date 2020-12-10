/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_tests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:17:48 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/19 15:25:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oh_test.h"
#include "libft.h"

const char		*test_ft_memcpy(void)
{
	const char		*str;
	char			buf[16];

	str = "Amazingness";
	ft_memcpy(buf, str, 11);
	buf[11] = '\0';
	OH_ASSERT("Memcpy didnt work", ft_strequ(buf, str));
	str = "Retardedness";
	ft_memcpy(buf, str, 12);
	buf[12] = '\0';
	OH_ASSERT("Memcpy didnt work", ft_strequ(buf, str));
	return (0);
}

const char		*test_ft_memcpy_ints(void)
{
	int32_t			nb;
	int32_t			dst;

	nb = 256;
	dst = 111;
	ft_memcpy(&dst, &nb, sizeof(nb));
	OH_ASSERT("Memcpy didnt work for int32", dst == nb);
	return (0);
}
