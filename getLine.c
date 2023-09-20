#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        if (info->environ)
            free_string_array(info->environ); // Free the existing environ array if it exists

        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
    if (!info->env || !var)
        return 0;

    int env_changed = 0;
    list_t *prev = NULL;
    list_t *current = info->env;

    while (current)
    {
        char *p = starts_with(current->str, var);
        if (p && *p == '=')
        {
            if (prev)
                prev->next = current->next;
            else
                info->env = current->next;

            free(current->str);
            free(current);
            env_changed = 1;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (env_changed)
        info->env_changed = 1;

    return env_changed;
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
    if (!var || !value)
        return 0;

    char *buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return 1;

    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);

    list_t *current = info->env;

    while (current)
    {
        char *p = starts_with(current->str, var);
        if (p && *p == '=')
        {
            free(current->str);
            current->str = buf;
            free(buf);
            info->env_changed = 1;
            return 0;
        }
        current = current->next;
    }

    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return 0;
}
