#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the maximum number of characters to be copied
 * Return: the destination string
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
    char *d = dest;
    const char *s = src;

    while (n > 0 && *s != '\0')
    {
        *d++ = *s++;
        n--;
    }

    while (n > 0)
    {
        *d++ = '\0';
        n--;
    }

    return dest;
}

/**
 * _strncat - concatenates two strings
 * @dest: the destination string
 * @src: the source string
 * @n: the maximum number of characters to be concatenated
 * Return: the destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    char *d = dest;
    const char *s = src;

    while (*d != '\0')
    {
        d++;
    }

    while (n > 0 && *s != '\0')
    {
        *d++ = *s++;
        n--;
    }

    *d = '\0';

    return dest;
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: a pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found
 */
char *_strchr(const char *s, int c)
{
    while (*s != '\0')
    {
        if (*s == c)
        {
            return (char *)s;
        }
        s++;
    }

    if (c == '\0')
    {
        return (char *)s;
    }

    return NULL;
}
