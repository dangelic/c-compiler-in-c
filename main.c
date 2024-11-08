#include <stdio.h>
#include "helpers/vector.h"
#include "compiler.h"
int main()
{
    int res = compile_file("./test.c", "./test", 0);
    if(res == COMPILER_FILE_COMPILED_OK) 
    {
        printf("compilation successfull\n");

    } 
    else if(COMPILER_FAILED_WITH_ERRORS)
    {
        printf("compilation failed\n");
    } 
    else 
    {
        printf("unknown response for compile time\n");
    }
    return 0;
}