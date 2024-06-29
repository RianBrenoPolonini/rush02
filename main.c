#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// Função para concatenar strings com alocação dinâmica de memória
char *concat_strings(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *result = malloc(len1 + len2 + 1); // +1 para o terminador nulo
    
    if (result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

char *number_to_words(long long num) {
    // Dicionário com os números por extenso até 20 e dezenas até 90
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
    
    // Lista das potências de 10 com seus nomes por extenso
    char *power_dict[] = {
        "", "hundred", "thousand", "million", 
        "billion", "trillion", "quadrillion", 
        "quintillion", "sextillion", "septillion", 
        "octillion", "nonillion", "decillion", 
        "undecillion"
    };
    
    // Variáveis para construir a string de resultado
    char *result = NULL;
    char *temp = NULL;
    
    // Números negativos
    if (num < 0) {
        temp = number_to_words(-num);
        result = concat_strings("negative ", temp);
        free(temp);
        return result;
    }
    
    // Números menores que 20
    if (num < 20) {
        result = strdup(num_dict[num]);
        return result;
    }
    
    // Números menores que 100
    if (num < 100) {
        int tens = num / 10;
        int ones = num % 10;
        if (ones == 0) {
            result = strdup(tens_dict[tens]);
        } else {
            char *ones_str = strdup(num_dict[ones]);
            result = concat_strings(tens_dict[tens], "-");
            temp = result;
            result = concat_strings(result, ones_str);
            free(temp);
            free(ones_str);
        }
        return result;
    }

    // Números menores que 1000
    if (num < 1000) {
        int hundreds = num / 100;
        int remainder = num % 100;
        char *hundreds_str = strdup(num_dict[hundreds]);
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
    
    // Encontrar a potência de 10 mais alta no dicionário
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

int main() {
    long long num;
    char *words;
    char buffer[1024];
    
    printf("Digite um número para convertê-lo em texto:\n");
    read(STDIN_FILENO, buffer, sizeof(buffer));
    num = atoll(buffer);
    
    words = number_to_words(num);
    
    // Usando a função write para imprimir o resultado
    int fd = open("/dev/stdout", O_WRONLY);
    write(fd, words, strlen(words));
    write(fd, "\n", 1);
    close(fd);
    
    free(words);
    
    return 0;
}
