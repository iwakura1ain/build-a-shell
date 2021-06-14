
#ifndef TOKEN_PARSER
#define TOKEN_PARSER
#include "token_parser.h"
#endif

int IsEmpty(char *token){
    int i;

    for(i=0; i<(int)strlen(token); i++){
        if(token[i] != ' ')
            return 0;
    }

    return 1;
    
}

void Tokenizer(char *input, struct Tokens *tokens){ 
    char *parse_point = input;
    char temp_delim = '\0';
    int i=0, j=0;
    
    //struct Tokens tokens = {.token_array=malloc(sizeof(char*)*30), .token_count=0};
    //struct Tokens *tokens = malloc(sizeof(struct Tokens));
    
    while(input[i]){
        for(j=0; j<DELIM_LEN; j++){
            if(input[i] == DELIMS[j]){
                //if(DELIMS[j] != ' ')  //append delims that are not ' '
                temp_delim = DELIMS[j];

                input[i] = '\0';
                if(!IsEmpty(parse_point)){
                    tokens->token_array[tokens->token_count] = malloc(sizeof(char) * strlen(parse_point));
                    strcpy(tokens->token_array[tokens->token_count], parse_point);                 

                     tokens->token_count++;
                }

                if(temp_delim){
                    tokens->token_array[tokens->token_count] = malloc(sizeof(char) * 2);
                    tokens->token_array[tokens->token_count][0] = DELIMS[j];
                    tokens->token_array[tokens->token_count][1] = '\0';

                    parse_point = &input[i+1];
                    tokens->token_count++;
                }
                    
                break;
            }
        }
        temp_delim = '\0';
        i++;
    }

    //last token
    if(!IsEmpty(parse_point)){
        tokens->token_array[tokens->token_count] = malloc(sizeof(char) * (strlen(parse_point)));
        strcpy(tokens->token_array[tokens->token_count], parse_point);
        tokens->token_count++;
    }
  

    return;
}

