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

#ifndef TOKEN_PARSER
#define TOKEN_PARSER
#include "token_parser.h"
#endif

#ifndef POSTFIX_PARSER
#define POSTFIX_PARSER
#include "postfix_parser.h"
#endif

#include "execute.h"


/*
char CURRENT_DIR[100] = "";
const char DELIMS[] = {';', '(', ')', '<', '>', '&', '|' };
const int DELIM_LEN = 7;
*/

/*
struct BuiltIn_Fuctions{  
    char name[10];
    void (*function)(char**);
}BUILTIN_FUNCTIONS[4] = {{"quit", &Quit},
                         {"ls",   &List_Dir},
                         {"cd",   &Change_Dir},
                         {"pwd",  &Print_Curr_Dir}};

void Change_Line(char **tokens){
    fprintf(stderr, "Change_Line called");
    printf("\n");
}

void Quit(char **tokens){
    fprintf(stderr, "Quit called");
    free(tokens);
    exit(0);
}

void List_Dir(char **tokens){
    fprintf(stderr, "List_Dir called");
}

void Change_Dir(char **tokens){
    fprintf(stderr, "Change_Dir called");
}

void Print_Curr_Dir(char **tokens){
    fprintf(stderr, "Print_Curr_Dir called");
}

void ExecLine(char **tokens, int count){ //maybe limit program to first token instead of 1 in all tokens 
    int i, j;

    for(i=0; i<count; i++){
        //fprintf(stderr, "%s ", tokens[i]);
        for(j=0; j<4; j++){
            if(!strcmp(tokens[i], BUILTIN_FUNCTIONS[j].name)){
                fprintf(stderr, "\nrunning built-in function\n");
                BUILTIN_FUNCTIONS[j].function(tokens);
                return;
            }
        }
        
    }

    fprintf(stderr, "\nrunning external function");
    //ExecExternal(tokens);
}


*/

/*
  char **Tokenizer(char **input, char *delim){
  char **token_array= malloc(sizeof(char*) * 30);
  char *token = NULL;
  int i=0, len=0;

  while(input[i]){
  token = strtok(input[i], delim);
  while(token){
  token_array[len] = malloc(sizeof(char)*strlen(token));
  strcpy(token_array[len], token);
  len++;
            
  token_array[len] = malloc(sizeof(char)*strlen(delim));
  strcpy(token_array[len], delim);
  len++;
            
  token = strtok(NULL, delim);
  }
  i++;
  }
  free(input);
    
  return token_array;
  }
*/  

/*
struct Tokens{
  char *token_array[30];
  int token_count;
};


void ClearTokens(struct Tokens* tokens){
    int i;

    for(i=0; i<tokens->token_count; i++){
        free(tokens->token_array[i]);
    }

    memset(tokens->token_array, 0, sizeof(char*)*30);
    tokens->token_count = 0;
        
}

void Tokenizer(char *input, struct Tokens *tokens){ 
    char *parse_point = input;
    char temp_delim = '\0';
    int i=0, j=0;
    
    //struct Tokens tokens = {.token_array=malloc(sizeof(char*)*30), .token_count=0};
    //struct Tokens *tokens = malloc(sizeof(struct Tokens));

    ClearTokens(tokens);
    while(input[i]){
        for(j=0; j<DELIM_LEN; j++){
            if(input[i] == DELIMS[j]){
                if(DELIMS[j] != ' ')  //append delims that are not ' '
                    temp_delim = DELIMS[j];

                input[i] = '\0';
                tokens->token_array[tokens->token_count] = malloc(sizeof(char) * strlen(parse_point));
                strcpy(tokens->token_array[tokens->token_count], parse_point);

                parse_point = &input[i+1];
                tokens->token_count++;

                if(temp_delim){
                    tokens->token_array[tokens->token_count] = malloc(sizeof(char) * 2);
                    tokens->token_array[tokens->token_count][0] = DELIMS[j];
                    tokens->token_array[tokens->token_count][1] = '\0';
                        
                    tokens->token_count++;
                }
                    
                break;
            }
        }
        temp_delim = '\0';
        i++;
    }

    //rest of remaining string
    tokens->token_array[tokens->token_count] = malloc(sizeof(char) * strlen(parse_point));
    strcpy(tokens->token_array[tokens->token_count], parse_point);
    tokens->token_count++;
    
    free(input);
    return;
}
*/    

/*
    //input = GetInput();
    if(input){
        for(i=0, token=strtok(input, delim); token!=NULL && i<=13; i++){  //checks for null token & max token array
            token_array[i] = malloc(sizeof(char) * strlen(token));  //Remember to free once token is used
            strcpy(token_array[i], token);

            token = strtok(NULL, delim);
        }
        free(input);
        return i;
    }
    else
        return 0;
    */
    


/*
void ParseToken(char *token){
    int i;

    while(1){
        if(token[i] == "\n"){
            token[i] = "";
        }
    }
}
*/

/*
void ParseTokens(char **tokens){
    int count = 0;

    while(1){
        if(tokens[count]){
            fprintf(stderr, "\ntoken %d: %s", count, tokens[count]);
            count++;
        }
        else
            break;
    }

    ExecLine(tokens, count);
    //FreeTokens(tokens);

}
*/

/*

struct Operator_Stack{  //basic implementation with top index 
    char* Stack[50];
    int top; //top element index
};

void Push_Operator(char *op, struct Operator_Stack Operators){
    if(Operators.top >= 50)  //shitty attempt at overflow protection
        return;
    
    Operators.Stack[Operators.top] = op;
    Operators.top++;
}

char* Pop_Operator(char *op, struct Operator_Stack Operators){
    char* pop_value = NULL;

    if(Operators.top < 0)
        return pop_value;
    else{
        pop_value = Operators.Stack[Operators.top];
        Operators.top--;

        return pop_value;
    }
}

struct Block_Queue{  //implementation with queue qrowing from the middle
    char* Queue[50];
    int push_index; //push point index
    int pop_index; //pop point index
    
};

void Push_Block(char *block, struct Block_Queue Block){
    int i;

    if( (Block.push_index <= 0 && Block.pop_index >= 49) || (Block.push_index > Block.pop_index) ) //shitty attempt at overflow prevention
        return;
    
    if(Block.push_index == 1 && Block.pop_index+5 < 50){ //no space to push on queue
        //TODO: implementat realloc of queue
        for(i=Block.pop_index; i>Block.push_index; i++){  //shift items right by 5
            Block.Queue[i+5] = Block.Queue[i];
        }

        Block.push_index += 5;
        Block.pop_index += 5;
    }
        
    Block.Queue[Block.push_index] = block;
    Block.push_index--;
}

char* Pop_Block(char *block, struct Block_Queue Block){
    char *pop_value = NULL;

    if(Block.pop_index >= 50){ //no space left on queue
        //TODO: implement realloc of queue
        return pop_value;
    }
    else{
        pop_value = Block.Queue[Block.pop_index];
        Block.Queue[Block.pop_index] = NULL;
        Block.pop_index--;
        
        return pop_value;
    }
}

*/

/*
char** PostfixParser(char *input){
    struct Operator_Stack operators = {.Stack={NULL}, .top=0};
    struct Block_Queue blocks = {.Queue={NULL}, .push_index=25, .pop_index=25};

        
    
    
}
*/

void Banner(){
    printf("dks's shell started :D");
}

void Prompt(){
    CURRENT_DIR = getcwd(CURRENT_DIR, 100);
    //printf("\n%s $ >> ", CURRENT_DIR);
    printf("\n$ >> ");
}

char* GetInput(){
    char *buf = NULL;
    size_t buf_size = 100;
    size_t buf_len = 0;

    buf_len = getline(&buf, &buf_size, stdin);
    fprintf(stderr, "inputted: %s", buf);

    if(buf_len)
        return buf;
    else
        return NULL;   
}
/*
char *SplitTok(char *input, char delim){
    char *split=NULL, *parse_point=NULL;
    int i;

    i=0;
    if(input)
        parse_point = input;
    else{
        while(input[i] != '\0')
            i++;
        parse_point = &input[i+1];        
    }

    i=0;
    while(parse_point[i] != delim && parse_point[i] != '\0')
        i++;
    parse_point[i] = '\0';

    split = malloc(strlen(parse_point));
    strcpy(split, parse_point);

    return split;      
}
*/

void ClearTokens(struct Tokens* tokens){
    int i;

    i=0;
    while(tokens->token_array[i]){  //only needs to free once, postfix[30] uses pointers from token[30]
        free(tokens->token_array[i]);
        i++;        
    }
    memset(tokens->token_array, 0, sizeof(char*)*30);
    memset(tokens->postfix_array, 0, sizeof(char*)*30);
       
    tokens->token_count = 0;
}

int main(){
    struct Tokens tokens = {.token_array={NULL}, .postfix_array={NULL}, .token_count=0};
    CURRENT_DIR = malloc(sizeof(char) *100); //fixed size, must implement realloc
    char *input = NULL, *split_input = NULL, *input_copy = NULL;
    int i;
    
    Banner();
    while(1){
        Prompt();
        input = GetInput();

        //split input by ';'
        split_input = strtok(input, ";\n");  
        while(split_input){
            fprintf(stderr, "\nsplit: %s\n", split_input);
            input_copy = malloc(sizeof(char) * strlen(split_input));            
            strcpy(input_copy, split_input);

            //split input by DELIMS into token blocks
            fprintf(stderr, "\ntokens:\n");
            Tokenizer(input_copy, &tokens);  
            for(i=0; i<tokens.token_count; i++){
                fprintf(stderr, "\n%d[%s]", i, tokens.token_array[i]);
            }             

            //sort token blocks by precedence 
            fprintf(stderr, "\nPostfix:\n");  
            PostfixSorter(&tokens);  
            for(i=0; i<tokens.token_count; i++){
                fprintf(stderr, "\n%d[%s]", i, tokens.postfix_array[i]);
            }

            //evaluate and execute sorted token blocks 
            fprintf(stderr, "\nExecution:\n");
            PostfixEval(&tokens);  

            //split input by ';'
            split_input = strtok(NULL, ";\n");  
            ClearTokens(&tokens);
            free(input_copy);
        }
        
    }
    
    free(input);
}
