#include "minishell.h"

/* read_word:
**	Reads a sequence of characters from the input and builds
**	a word token until a space or operator is encountered.
**
**	This function also handles quoted substrings:
**	- If quotes are found, read_quoted is called
**	- Quotes are removed from the final string
**	- The quote type is recorded (single or double)
**
**	The result is a dynamically built string representing
**	a full argument or word in the command.
**
**	Returns:
**	- Newly allocated string containing the word
**	- NULL on allocation failure
*/
char *read_word(char *input, int *i, t_quote_type *quote)
{
    char            *buffer;
    char            *piece;
    char            *tmp;
    t_quote_type    q;

    buffer = ft_strdup("");
    if (!buffer)
        return (NULL);
    *quote = NO_QUOTE;
    while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))
    {
        if (input[*i] == '\'' || input[*i] == '"')
        {
            piece = read_quoted(input, i, &q);
            if (piece && q == SINGLE_QUOTE && *quote == NO_QUOTE)
                *quote = SINGLE_QUOTE;
            else if (piece && *quote == NO_QUOTE)
                *quote = DOUBLE_QUOTE;
        }
        else
        {
            piece = ft_substr(input, *i, 1);
            (*i)++;
        }
        if (!piece)
        {
            free(buffer);
            return (NULL);
        }
        tmp = strjoin_free(buffer, piece);
        free(piece);
        if (!tmp)
        {
            free(buffer);
            return (NULL);
        }
        buffer = tmp;
    }
    return (buffer);
}
/*
Responsibilities:

1️. Detect operator type
2️. Get operator length
3️. Extract operator string
4️. Create token
5️. Advance index
*/
/* create_operator_token:
**	Detects and creates a token for shell operators such as:
**	|, <, >, >>, <<
**
**	The function:
**	- Determines operator length (1 or 2 characters)
**	- Extracts the operator string
**	- Determines its type (PIPE, REDIR, etc.)
**	- Creates a corresponding token
**
**	The input index is advanced accordingly.
**
**	Returns:
**	- Newly created token
**	- NULL on failure
*/
t_token *create_operator_token(char *input, int *i)
{
    int             len;
    char            *op;
    t_token         *token;
    t_token_type    type;

    len = operator_length(&input[*i]);
    if (len <= 0)
        return (NULL);
    op = ft_substr(input, *i, len);
    if (!op)
        return (NULL);
    type = operator_type(op);
    token = token_create(type, op, NO_QUOTE);
    free(op);
    if (!token)
        return (NULL);
    *i += len;
    return (token);
}

/* lexer:
**	Main lexical analysis function that converts the raw input
**	string into a linked list of tokens.
**
**	It iterates through the input and:
**	- Skips whitespace
**	- Detects operators and creates operator tokens
**	- Reads words (including quoted parts) using read_word
**
**	Each token is appended to a linked list representing the
**	tokenized input.
**
**	On error, all allocated tokens are freed.
**
**	Returns:
**	- Head of the token list on success
**	- NULL on failure
*/
t_token *lexer(char *input)
{
    int             i;
    t_token         *tokens;
    t_token         *token;
    char            *word;
    t_quote_type    quote;

    i = 0;
    tokens = NULL;

    while (input[i])
    {
        while (input[i] && is_space(input[i]))
            i++;

        if (!input[i])
            break ;

        if (is_operator(input[i]))
            token = create_operator_token(input, &i);
        else
        {
            word = read_word(input, &i, &quote);
            if (!word)
            {
                token_clear(&tokens);
                return (NULL);
            }

            token = token_create(WORD, word, quote);
            free(word);
        }

        if (!token)
        {
            token_clear(&tokens);
            return (NULL);
        }

        token_add_back(&tokens, token);
    }

    return (tokens);
}

/* read_quoted:
**	Extracts a substring enclosed in quotes (single or double).
**
**	The function:
**	- Detects the quote type
**	- Skips the opening quote
**	- Reads until the matching closing quote
**	- Returns the inner content without quotes
**
**	The input index is updated to continue parsing after
**	the closing quote.
**
**	Returns:
**	- Newly allocated string without quotes
**	- NULL on failure
*/
char *read_quoted(char *input, int *i, t_quote_type *quote)
{
    char    q;
    int     start;
    char    *str;

    q = input[*i];
    if (q == '\'')
        *quote = SINGLE_QUOTE;
    else
        *quote = DOUBLE_QUOTE;

    (*i)++;
    start = *i;

    while (input[*i] && input[*i] != q)
        (*i)++;

    str = ft_substr(input, start, *i - start);
    if (!str)
        return (NULL);
    if (input[*i] == q)
        (*i)++;

    return (str);
}
