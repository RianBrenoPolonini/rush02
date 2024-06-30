/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfaria-p <rfaria-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:02:33 by rfaria-p          #+#    #+#             */
/*   Updated: 2024/06/30 12:20:22 by rfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_str_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = ft_str_len(dest);
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*concat_strings(const char *str1, const char *str2)
{
	char	*result;

	result = malloc(ft_str_len(str1) + ft_str_len(str2) + 1);
	if (!result)
		exit(EXIT_FAILURE);
	ft_strcpy(result, str1);
	ft_strcat(result, str2);
	return (result);
}

char	*ft_strdup(const char *str)
{
	int		len;
	char	*dup;

	len = ft_str_len(str);
	dup = malloc(len + 1);
	if (!dup)
		exit(EXIT_FAILURE);
	ft_strcpy(dup, str);
	return (dup);
}
