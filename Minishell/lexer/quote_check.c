#include "minishell.h"

int check_quotes(char *input)
{
    int     i;
    char    quote;

    if (!input)
        return (1);
    i = 0;
    quote = 0;
    while (input[i])
    {
        if (quote == 0 && (input[i] == '\'' || input[i] == '"'))
            quote = input[i];
        else if (quote != 0 && input[i] == quote)
            quote = 0;
        i++;
    }
    if (quote != 0)
    {
        write(2, "minishell: unclosed quote\n", 26);
        return (1);
    }
    return (0);
}
