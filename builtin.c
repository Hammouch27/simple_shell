#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
    int exit_code = 0;

    if (info->argv[1]) /* If there is an exit argument */
    {
        exit_code = _erratoi(info->argv[1]);
        if (exit_code == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return (1);
        }
    }
    info->err_num = exit_code;
    return (-2); // Returning -2 indicates an exit request
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
    char *dir = NULL;
    char buffer[1024];

    if (!info->argv[1])
    {
        // If no directory is provided, change to the home directory
        dir = _getenv(info, "HOME=");
        if (!dir)
            dir = _getenv(info, "PWD=");
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        // If '-' is provided, change to the previous directory
        dir = _getenv(info, "OLDPWD=");
        if (!dir)
        {
            _puts("OLDPWD not set.\n");
            return (1);
        }
    }
    else
    {
        // Change to the specified directory
        dir = info->argv[1];
    }

    int chdir_ret = chdir(dir);

    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(dir);
        _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * _myhelp - displays help information
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
    // Display help information for your shell
    _puts("Shell Help:"); // Add your help information here
    return (0);
}
