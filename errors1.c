#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
    int result = 0;
    int sign = 1;

    if (*s == '-')
    {
        sign = -1;
        s++;
    }
    else if (*s == '+')
    {
        s++;
    }

    for (; *s != '\0'; s++)
    {
        if (*s >= '0' && *s <= '9')
        {
            if (result > INT_MAX / 10 || (result == INT_MAX / 10 && (*s - '0') > INT_MAX % 10))
            {
                return -1; // Overflow
            }
            result = result * 10 + (*s - '0');
        }
        else
        {
            return -1; // Invalid character in the string
        }
    }

    return result * sign;
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: None
 */
void print_error(info_t *info, char *estr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
    int count = 0;

    if (input < 0)
    {
        _putfd('-', fd);
        input = -input;
        count++;
    }

    int divisor = 1;
    while (input / divisor >= 10)
    {
        divisor *= 10;
    }

    while (divisor != 0)
    {
        int digit = input / divisor;
        _putfd(digit + '0', fd);
        count++;
        input %= divisor;
        divisor /= 10;
    }

    return count;
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
    static char buffer[50];
    char *ptr = &buffer[49];
    *ptr = '\0';
    char sign = 0;

    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }

    char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
    {
        *--ptr = sign;
    }

    return ptr;
}

/**
 * remove_comments - function replaces the first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: None
 */
void remove_comments(char *buf)
{
    for (int i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (i == 0 || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
    }
}
