#include "command.h"
#include <stddef.h>
#include <stdio.h>

#define MAX_ARGS 10

void wish_exit(char **args)
{
    if (args != NULL)
    {
        // If exit has an argument
        print_error();
    }
    // good exit
    exit(0);
}

void wish_path(char **args, char **path)
{
    // Free previously allocated memory (assuming it was done)
    for (int i = 0; path[i] != NULL; i++)
    {
        free(path[i]);
    }

    // Set path to default path if no arguments provided
    if (args == NULL)
    {
        // Allocate memory for default paths
        path[0] = strdup("/bin");
        path[1] = strdup("");
        return;
    }

    // Copy arguments to path (assuming they are valid)
    for (int i = 0; i < MAX_ARGS; i++)
    {
        if (args[i] == NULL)
        {
            break;
        }
        path[i] = strdup(args[i]);
    }
}

void wish_cd(char **args)
{
    // custom cd call
    if (args == NULL || args[1] != NULL)
        print_error();
    chdir(args[0]);
}

int check_for_redirect(char **args)
{
    if (args == NULL)
        return -1;
    // Check for separate argument
    for (int i = 0; i < MAX_ARGS; i++)
    {
        if (args[i] == NULL)
            break;
        else if (strcmp(args[i], ">") == 0)
            return i;
    }

    // Check for contained within argument
    for (int i = MAX_ARGS; i >= 0; i--)
    {
        if (args[i] == NULL)
            continue;
        for (int j = 0; j < strlen(args[i]); j++)
        {
            if (args[i][j] == '>')
            {
                char *destination = malloc(100);
                strcpy(destination, args[i]);
                args[i] = strsep(&destination, ">");
                args[i + 1] = ">";
                args[i + 2] = destination;
                return i + 1;
            }
        }
    }

    return -1;
}

void wish_redirect(char **args, int redir_index)
{
    // args[redir_index] is guaranteed to be >
    if (args[redir_index + 1] == NULL || args[redir_index + 2] != NULL)
    {
        // No path to redirect or multiple redirects
        print_error();
    }
    else
    {
        freopen(args[redir_index + 1], "w", stdout);
        // Set the redirect args to NULL so they don't get passed to the command
        args[redir_index] = NULL;
        args[redir_index + 1] = NULL;
    }
}