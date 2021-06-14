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

/*
struct Process{    
    char **call_block;    //token block that called the process

    FILE *file;            
    int pipe[2];
    
    void (*function)(struct Process*);  //function to start process
    pid_t pid;            //pid of process

    //void *result;         //result    
    int exit_status;      //exit status
};
*/

struct Block{
    char *call_block;
    
    FILE *file;
    void (*function)(struct Block*);
    
    char *result;
    int exit_status;  
};

struct Block_Stack{
    struct Block *stack[20];
    int top;
};

struct BuiltIn_Functions{
    char name[10];
    void (*function)(struct Process*);
};


void Change_Line(struct Process *process);
void Quit(struct Process *process);
void List_Dir(struct Process *process);
void Change_Dir(struct Process *process);
void Print_Curr_Dir(struct Process *process);
void ExecExternal(struct Process *process);

struct Process* GetProcess(char *token);
char **ParseBlock(char *token);
void (*GetFunction(struct Process *process))(struct Process *process);
int CheckIfFile(struct Process *process);
void FreeProcess(struct Process *process);

struct Process* Pop_P_Stack(struct Process_Stack *stack);
void Push_P_Stack(struct Process_Stack *stack, struct Process *process);
void PostfixEval(struct Tokens *tokens);

struct Process* PipeOperation(struct Process *p1, struct Process *p2);
struct Process* OrOperation(struct Process *p1, struct Process *p2);
struct Process* AndOperation(struct Process *p1, struct Process *p2);



