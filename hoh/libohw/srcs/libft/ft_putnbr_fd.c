/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <hoh@student.42.kr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:22:26 by ohw               #+#    #+#             */
/*   Updated: 2022/07/27 13:50:31 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	*buf;

	buf = ft_itoa(n);
	ft_putstr_fd(buf, fd);
	free(buf);
	buf = 0;
}
