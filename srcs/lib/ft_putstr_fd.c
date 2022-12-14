/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:42:11 by zweng             #+#    #+#             */
/*   Updated: 2022/10/21 18:11:06 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_putstr_fd(char const *str, int fd)
{
	size_t	len;

	if (!str)
		return ;
	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
}
