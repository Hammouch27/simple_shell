#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
    // Print the current environment variables
    print_list_str(info->env);
    return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value or NULL if not found
 */
char *_getenv(info_t *info, const char *name)
{
    // Search for the specified environment variable
    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0 on success, 1 on error
 */
int _mysetenv(info_t *info)
{
    // Check the number of arguments and set the environment variable
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    
    int ret = _setenv(info, info->argv[1], info->argv[2]);
    
    if (ret != 0)
    {
        _eputs("Error setting environment variable\n");
        return (1);
    }
    
    return (0);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0 on success, 1 on error
 */
int _myunsetenv(info_t *info)
{
    // Check the number of arguments and unset the environment variables
    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    
    int i;
    for (i = 1; i < info->argc; i++)
    {
        int ret = _unsetenv(info, info->argv[i]);
        if (ret != 0)
        {
            _eputs("Error unsetting environment variable\n");
            return (1);
        }
    }

    return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0 on success, 1 on error
 */
int populate_env_list(info_t *info)
{
    // Populate the environment linked list from the "environ" global variable
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
    {
        int ret = add_node_end(&node, environ[i], 0);
        if (ret != 0)
        {
            _eputs("Error populating environment list\n");
            return (1);
        }
    }

    info->env = node;
    return (0);
}
