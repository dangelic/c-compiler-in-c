#ifndef PEACHCOMPILER_H
#define PEACHCOMPILER_H

#include <studio.h>

struct pos
{
    int line;
    int col;
    const char* filename;
};

enum
{
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE,
}

struct token
{
    int type;
    int flags;
    union // shared memory; only one settable to save memory
    {
        char cval;
        const char* sval;
        unsigned int inum;
        unsigned long lnum;
        unsigned long long llnum;
        void* any;
    };

    // whitespace between token and next token?
    // e.g. *     a -> true for a
    bool whitespace;

    // (1+2+3); for debugging
    const char* between_brackets;
};
