#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> // For Windows-specific API

#define TK_BUFF_SIZE 64
#define TOK_DELIM " \t\r\n"
#define RED "\033[0;31m"
#define RESET "\033[0m"

char *read_line();
char **split_line(char *);
int dash_exit(char **);
int dash_execute(char **);

int dash_execute(char **args)
{
    // In Windows, replace fork and exec with system() call for simplicity
    if (strcmp(args[0], "exit") == 0)
    {
        return dash_exit(args);
    }

    // Use system call to execute the command
    int result = system(args[0]);
    if (result == -1)
    {
        printf(RED "dash: command not found: %s" RESET "\n", args[0]);
    }

    return 1;
}

int dash_exit(char **args)
{
    return 0;
}

char **split_line(char *line)
{
    int buffsize = TK_BUFF_SIZE, position = 0;
    char **tokens = malloc(buffsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= buffsize)
        {
            buffsize += TK_BUFF_SIZE;
            tokens = realloc(tokens, buffsize * sizeof(char *));

            if (!tokens)
            {
                fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;

    return tokens;
}

char *read_line()
{
    int buffsize = 1024;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        c = getchar();
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        if (position >= buffsize)
        {
            buffsize += 1024;
            buffer = realloc(buffer, buffsize);

            if (!buffer)
            {
                fprintf(stderr, "dash: Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void loop()
{
    char *line;
    char **args;
    int status = 1;

    do
    {
        printf("> ");
        line = read_line();
        args = split_line(line);
        status = dash_execute(args);
        free(line);
        free(args);
    } while (status);
}

int main()
{
    loop();
    return 0;
}
