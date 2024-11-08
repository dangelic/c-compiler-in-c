#include <string.h>
#include "compiler.h"
#include "helpers/vector.h"
#include "helpers/buffer.h"

// evaluates expression and if true write it to the buffer
#define LEX_GETC_IF(buffer, c, exp)     \
    for(c = peekc(); exp; c = peekc())  \
    {                                   \
        buffer_write(buffer, c);        \
        nextc();                        \
    }                                   \

static struct lex_process *lex_process;
static struct token tmp_token;

static char peekc()
{
    return lex_process->function->peek_char(lex_process);
}

static void pushc(char c)
{
    lex_process->function->push_char(lex_process, c);
}

static struct pos lex_file_position()
{
    return lex_process->pos;
}

struct token* token_create(struct token* _token)
{
    memcpy(&tmp_token, _token, sizeof(struct token));
    tmp_token.pos = lex_file_position();
    return &tmp_token;
}

static char nextc()
{
    char c = lex_process->function->next_char(lex_process);
    lex_process->pos.col += 1;
    if (c == '\n')
    {
        lex_process->pos.line += 1;
        lex_process->pos.col = 1;
    }

    return c;
}

const char* read_number_str()
{
    const char *num = NULL;
    struct buffer *buffer = buffer_create();
    char c = peekc();
    // ASCII-Number
    LEX_GETC_IF(buffer, c, (c >= '0' && c <= '9'));

    // 0x00 -> 0
    buffer_write(buffer, 0x00);
    return buffer_ptr(buffer);
}

// convert buffered numbers into string
unsigned long long read_number()
{
    const char *s = read_number_str();
    return atoll(s);
}

struct token* token_make_number_for_value(unsigned long number)
{
    return token_create(&(struct token){.type=TOKEN_TYPE_NUMBER,.llnum=number});
}

struct token* token_make_number()
{
    return token_make_number_for_value(read_number());
}

struct token *read_next_token()
{
    struct token *token = NULL;
    char c = peekc();
    switch(c)
    {
        NUMERIC_CASE:
            token = token_make_number();
            break;
        case EOF:
            break;
        default:
            compiler_error(lex_process->compiler, "Unexpected token\n");
    }

    return token;
}

int lex(struct lex_process *process) 
{
    process->current_expression_count = 0;
    process->parentheses_buffer = NULL;
    lex_process = process;
    process->pos.filename = process->compiler->cfile.abs_path;

    struct token *token = read_next_token();
    while(token)
    {
        vector_push(process->token_vec, token);
        token = read_next_token();
    }
    return LEXICAL_ANALYSIS_ALL_OK;
}
