/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:51:09 by dtolmaco          #+#    #+#             */
/*   Updated: 2023/11/16 14:33:29 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*new;

	if (!s)
		return (NULL);
	if (start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	size = ft_strlen(start + (char *)s);
	if (size < len)
		len = size;
	new = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(new, s + start, len + 1);
	return (new);
}
/*
#include <stdio.h>
int main()
{
	printf("%s\n",ft_substr("Red Hot Chili Peppers", 4, 12));
}*/
