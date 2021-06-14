#ifndef BASIC_LIB
#define BASIC_LIB
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#endif

#ifndef TOKEN_PARSER
#define TOKEN_PARSER
#include "token_parser.h"
#endif

#ifndef GLOBAL_VARS
#define GLOBAL_VARS
extern char *CURRENT_DIR;
extern const char DELIMS[];
extern const int DELIM_LEN;
#endif


struct Stack{  //basic implementation with top index 
    char *Stack[50];
    int top; //top element index
    int len;
};

struct Queue{  //implementation with queue qrowing from the middle
    char *Queue[50];
    int push_index; //push point index
    int pop_index; //pop point index
    int len;
    
};

void Push_Stack(char *op, struct Stack *Operators);
char* Pop_Stack(struct Stack *Operators);
char* Peek_Stack(struct Stack *Operators);

void Push_Queue(char *block, struct Queue *Block);
char* Pop_Queue(struct Queue *Block);

int IsOperator(char *token);
int GetPrecedence(char *op1, struct Stack *stack);
void PostfixSorter(struct Tokens *tokens);
int PostfixCheck(struct Tokens *tokens);
//struct Process* ExecOperation(struct Process *prev, struct Stack *stack, struct Tokens *tokens, int index);


