/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:47:17 by zweng             #+#    #+#             */
/*   Updated: 2022/10/21 18:25:47 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	pft_nbr(int n, int fd)
{
	int		digit;
	char	c;

	if (n >= 10 || n <= -10)
		pft_nbr(n / 10, fd);
	digit = n % 10 > 0 ? n % 10 : -(n % 10);
	c = '0' + digit;
	write(fd, &c, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write(fd, "-", 1);
	pft_nbr(n, fd);
}
