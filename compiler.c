#include "compiler.h"

struct lex_process_functions compiler_lex_functions = 
{
    .next_char=compile_process_next_char,
    .peek_char=compile_process_peek_char,
    .push_char=compile_process_push_char
};

int compile_file(const char *filename, const char *out_filename, int flags)
{
    ...
}