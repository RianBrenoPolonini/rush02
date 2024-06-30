/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfaria-p <rfaria-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:37:50 by rfaria-p          #+#    #+#             */
/*   Updated: 2024/06/30 11:25:58 by rfaria-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int ft_str_len(const char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_strcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *ft_strcat(char *dest, const char *src)
{
    int i = 0;
    int j = 0;
    
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

char *concat_strings(const char *str1, const char *str2)
{
    char *result;
    
    result = malloc(ft_str_len(str1) + ft_str_len(str2) + 1);
    if (!result)
        exit(EXIT_FAILURE);
    ft_strcpy(result, str1);
    ft_strcat(result, str2);
    return (result);
}

char *ft_strdup(const char *str) {
    int len;
    char *dup;

    len = ft_str_len(str);
    dup = malloc(len + 1);
    if (!dup) 
        exit(EXIT_FAILURE);
    ft_strcpy(dup, str);
    return (dup);
}

long long int ft_atoll(const char *str) {
    long long int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ')
        i++;
    if (str[i] == '-')
	{
        sign = -1;
		i++;
	}
	else if (str[i] == '+')
    	i++;
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return (result * sign);
}

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
        result = concat_strings("negative ", temp);
        free(temp);
        return result;
    }

    if (num < 20) {
        result = ft_strdup(num_dict[num]);
        return result;
    }

    if (num < 100) {
        int tens = num / 10;
        int ones = num % 10;
        if (ones == 0) {
            result = ft_strdup(tens_dict[tens]);
        } else {
            char *ones_str = ft_strdup(num_dict[ones]);
            result = concat_strings(tens_dict[tens], " ");
            temp = result;
            result = concat_strings(result, ones_str);
            free(temp);
            free(ones_str);
        }
        return result;
    }

    if (num < 1000) {
        int hundreds = num / 100;
        int remainder = num % 100;
        char *hundreds_str = ft_strdup(num_dict[hundreds]);
        temp = concat_strings(hundreds_str, " hundred");
        free(hundreds_str);
        if (remainder == 0) {
            result = temp;
        } else {
            char *remainder_str = number_to_words(remainder);
            result = concat_strings(temp, " ");
            free(temp);
            temp = result;
            result = concat_strings(temp, remainder_str);
            free(temp);
            free(remainder_str);
        }
        return result;
    }

    size_t i = 2; // Iniciar em "thousand"
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
    char *right_part = number_to_words(remainder);

    temp = concat_strings(left_part, " ");
    result = concat_strings(temp, power_dict[i]);
    free(temp);
    free(left_part);

    if (remainder != 0) {
        temp = result;
        result = concat_strings(result, " ");
        free(temp);
        temp = result;
        result = concat_strings(result, right_part);
        free(temp);
    }

    free(right_part);
    return result;
}

int main()
{
    long long num;
    char *words;
    char buffer[1024];

    printf("Digite um número para convertê-lo em texto:\n");
    read(STDIN_FILENO, buffer, sizeof(buffer));
    num = ft_atoll(buffer);

    words = number_to_words(num);

    // Usando a função write para imprimir o resultado
    int fd = open("/dev/stdout", O_WRONLY);
    write(fd, words, ft_str_len(words));
    write(fd, "\n", 1);
    close(fd);

    free(words);

    return 0;
}
