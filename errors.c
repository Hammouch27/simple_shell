#include "shell.h"
#include <unistd.h> // Include the header for the write function

/**
 * _eputs - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
    if (!str)
        return;

    while (*str)
    {
        _eputchar(*str);
        str++;
    }
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
    return write(STDERR_FILENO, &c, 1);
}

/**
 * _putfd - writes the character c to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
    return write(fd, &c, 1);
}

/**
 * _putsfd - prints an input string to a given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int _putsfd(char *str, int fd)
{
    if (!str)
        return 0;

    int count = 0;
    while (*str)
    {
        if (_putfd(*str, fd) == -1)
        {
            // Handle write error if needed
            return -1;
        }
        str++;
        count++;
    }
    return count;
}
