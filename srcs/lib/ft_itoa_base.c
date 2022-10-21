/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 13:37:51 by zweng             #+#    #+#             */
/*   Updated: 2022/10/21 18:42:40 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	pf_abs(int nbr)
{
	return (nbr < 0 ? -nbr : nbr);
}

static void	ft_aux(long long int val, int base, char **p)
{
	char	*base_str;
	int		tmp;

	base_str = "0123456789ABCDEF";
	if (val >= base || val <= -base)
		ft_aux(val / base, base, p);
	tmp = (int)(val % base);
	*(*p)++ = *(base_str + pf_abs(tmp));
}

void		ft_itoa_base(long long int value, int base)
{
	char	*p;
    char    res[100];

    ft_bzero(res, 100);
	if (base < 2 || base > 16)
		return ;
	p = res;
	if (value < 0 && base == 10)
		*p++ = '-';
	ft_aux(value, base, &p);
	*p = 0;
    ft_putstr(res);
}
