/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfaria-p <rfaria-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:37:50 by rfaria-p          #+#    #+#             */
/*   Updated: 2024/06/30 13:39:23 by rfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char *number_to_words(long long num) {
    char *num_dict[] = {
        "zero", "one", "two", "three", "four", 
        "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", 
        "fourteen", "fifteen", "sixteen", "seventeen", 
        "eighteen", "nineteen"
    };

    char *tens_dict[] = {
        "", "", "twenty", "thirty", "forty", 
        "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    char *power_dict[] = {
        "", "hundred", "thousand", "million", 
        "billion", "trillion", "quadrillion", 
        "quintillion", "sextillion", "septillion", 
        "octillion", "nonillion", "decillion", 
        "undecillion"
    };

    char *result = NULL;
    char *temp = NULL;

    if (num < 0) {
        temp = number_to_words(-num);
		if (!temp)
			return (NULL);
        result = concat_strings("negative ", temp);
        free(temp);
		if (!result)
			return (NULL);
        return result;
    }

    if (num < 20) {
        result = ft_strdup(num_dict[num]);
		if (!result)
			return (NULL);
        return result;
    }

    if (num < 100) {
        int tens = num / 10;
        int ones = num % 10;
        if (ones == 0) {
            result = ft_strdup(tens_dict[tens]);
			if (!result)
				return (NULL);
        } else {
            char *ones_str = ft_strdup(num_dict[ones]);
			if (!ones_str)
				return (NULL);
            result = concat_strings(tens_dict[tens], " ");
			if (!result)
			{
				free(ones_str);
				return (NULL);
			}
            temp = result;
            result = concat_strings(result, ones_str);
            free(temp);
            free(ones_str);
			if (!result)
				return (NULL);
        }
        return result;
    }

    if (num < 1000) {
        int hundreds = num / 100;
        int remainder = num % 100;
        char *hundreds_str = ft_strdup(num_dict[hundreds]);
		if (!hundreds_str)
			return (NULL);
        temp = concat_strings(hundreds_str, " hundred");
        free(hundreds_str);
		if (!temp)
			return (NULL);
        if (remainder == 0) {
            result = temp;
        } else {
            char *remainder_str = number_to_words(remainder);
			if (!remainder_str)
			{
				free(temp);
				return (NULL);
			}
            result = concat_strings(temp, " ");
            free(temp);
			if (!result)
			{
				free(remainder_str);
				return (NULL);
			}
            temp = result;
            result = concat_strings(temp, remainder_str);
            free(temp);
            free(remainder_str);
			if (!result)
				return (NULL);
        }
        return result;
    }

    size_t i = 2;
    long long power = 1000;
    while (i < sizeof(power_dict) / sizeof(power_dict[0])) {
        if (num < power * 1000) {
            break;
        }
        power *= 1000;
        i++;
    }

    long long quotient = num / power;
    long long remainder = num % power;
    char *left_part = number_to_words(quotient);
	if (!left_part)
		return (NULL);
    char *right_part = number_to_words(remainder);
	if (!right_part)
	{
		free(left_part);
		return (NULL);
	}

    temp = concat_strings(left_part, " ");
	free(left_part);
	if (!temp)
	{
		free(right_part);
		return (NULL);
	}
    result = concat_strings(temp, power_dict[i]);
    free(temp);
	if (!result)
	{
		free(right_part);
		return (NULL);
	}
    if (remainder != 0) {
        temp = result;
        result = concat_strings(result, " ");
        free(temp);
		if (!result)
		{
			free(right_part);
			return (NULL);
		}
        temp = result;
        result = concat_strings(result, right_part);
        free(temp);
		free(right_part);
		if (!result)
			return (NULL);
    } else {
		free(right_part);
	}
    return (result);
}

int	main()
{
	long long	num;
	char		*words;
	char		buffer[1024];

	printf("Digite um número para convertê-lo em texto:\n");
	read(STDIN_FILENO, buffer, sizeof(buffer));
	num = ft_atoll(buffer);
	words = number_to_words(num);
	if (!words)
		return (0);
	int fd = open("/dev/stdout", O_WRONLY);
	write(fd, words, ft_str_len(words));
	write(fd, "\n", 1);
	close(fd);
	free(words);
	return (0);
}
