
#ifndef BASIC_LIB
#define BASIC_LIB
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#endif


#ifndef GLOBAL_VARS
#define GLOBAL_VARS
extern char *CURRENT_DIR;
extern const char DELIMS[];
extern const int DELIM_LEN;
#endif

struct Tokens{
    char *token_array[30];
    char *postfix_array[30];
    int token_count;
};

void Tokenizer(char *input, struct Tokens *tokens);
void ParseTokens(char **tokens);






