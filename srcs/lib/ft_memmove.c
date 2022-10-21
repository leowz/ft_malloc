/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:48:16 by zweng             #+#    #+#             */
/*   Updated: 2022/10/21 18:06:48 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dst, const void *src, unsigned int len)
{
	char		*dp;
	const char	*sp;

	dp = dst;
	sp = src;
	if (dp < sp)
	{
		while (len-- > 0)
			*dp++ = *sp++;
	}
	else
	{
		dp += len;
		sp += len;
		while (len-- > 0)
			*--dp = *--sp;
	}
	return (dst);
}
