#ifndef EXECUTE
#define EXECUTE
#include "execute.h"
#endif

const int BUILTIN_LEN = 5;
struct BuiltIn_Functions BUILTIN_FUNCTIONS[5] = {{"default", &ExecExternal},
                                                           {"quit", &Quit},
                                                           {"ls",   &List_Dir},
                                                           {"cd",   &Change_Dir},
                                                           {"pwd",  &Print_Curr_Dir}};


void Quit(struct Process *process){
    fprintf(stderr, "Quit called");
    process->exit_status = 1;
    //TODO: free data
    exit(0);
}

void List_Dir(struct Process *process){    
    fprintf(stderr, "List_Dir called");
    process->exit_status = 1;
}

void Change_Dir(struct Process *process){
    fprintf(stderr, "Change_Dir called");
    process->exit_status = 1;
}

void Print_Curr_Dir(struct Process *process){
    fprintf(stderr, "Print_Curr_Dir called");
    process->exit_status = 1;
}

void ExecExternal(struct Process *process){ //fork & exec external programs    
    //save child pid
    //wait for child process to end, then save exit status

    fprintf(stderr, "exec external");

}

struct Process* Pop_P_Stack(struct Process_Stack *stack){
    struct Process *result = NULL;
    
    if(stack->top == 0){
        result = stack->stack[stack->top];
        stack->stack[stack->top] = NULL;
        stack->top--;
        
        return result;
    }
    else
        return NULL;
}

void Push_P_Stack(struct Process_Stack *stack, struct Process *process){
    stack->stack[stack->top] = process;
    stack->top++;
}

struct Block* GetBlock(char *token){  //OOP in C?! WTF?
    struct Block *block = malloc(sizeof(struct Block));    

    block->call_block = token;
    block->file = NULL;
    block->function = NULL;
    block->result = NULL;
    block->exit_status = -1;

    return block;
}

char **ParseBlock(char *token){
    char *parse_point=NULL;
    char **token_blocks = malloc(sizeof(char*)*15);
    memset(token_blocks, 0, sizeof(char*)*15);
    
    int i=0;

    parse_point = strtok(token, " ");
    while(parse_point && i<15){
        token_blocks[i] = malloc(sizeof(char) * (strlen(parse_point) +1));
        strcpy(token_blocks[i], parse_point);

        strtok(NULL, " ");
        i++;
    }
    
    return token_blocks;
}

//stackoverflow.com/questions/25671410/function-that-returns-a-function-pointer-syntax  
void (*GetFunction(struct Process *process))(struct Process *process){  //returns function to execute
    int i;

    for(i=0; i<BUILTIN_LEN; i++){
        if( !strcmp(process->call_block[0], BUILTIN_FUNCTIONS[i].name) )
            return BUILTIN_FUNCTIONS[i].function;
    }

    return BUILTIN_FUNCTIONS[0].function;
}

void FreeProcess(struct Process *process){
    int i=0;

    while(process->call_block[i]){
        free(process->call_block[i]);
        i++;
    }

    free(process);
}

void PostfixEval(struct Tokens *tokens){
    struct Block_Stack stack = {.stack={NULL}, .top=0};
    char *token = NULL;
    int i;
    
    for(i=0; i<tokens->token_count; i++){
        token = tokens->postfix_array[i];

        switch(IsOperator(token)){
        case 0:  //operator = '|'
            
            Push_P_Stack(&p_stack, result);
            break;
        case 1:  //operator = '>'
            
            Push_P_Stack(&p_stack, result);
            break;
        case 1:  //operator = '='
            
            Push_P_Stack(&p_stack, result);
            break;
        case 1:  //operator = '~'
            
            Push_P_Stack(&p_stack, result);
            break;
        case 1:  //operator = '-'
            
            Push_P_Stack(&p_stack, result);
            break;
        case 1:  //operator = '&'
            
            Push_P_Stack(&p_stack, result);
            break;
        case 5:  //operator = '!'
            
            Push_P_Stack(&p_stack, result);
            break;
        default: //is command block 
            Push_P_Stack(&p_stack, GetBlock(token));
            break;
        
        }
        
    }
   
}

struct Process* FileOperation(struct Process *p1, struct Process *p2, char *op){
    
}

struct Process* PipeOperation(struct Process *p1, struct Process *p2, char *op){
    int i = CheckIfFile(p1)*10 + CheckIfFile(p2);

    fprintf(stderr, "\n OPERATION: OR\n");
    switch(i){
    case 0:  //process > processes
        p2->pipe[1] = p1->pipe[0];
        //fork&run p2
        //fork&run p1
        p2->function(p2);
        p1->function(p1);
        break;
        
    case 1:  //process > file
        //run p1, read stdout
        //write to p2
        p1->function(p1);
        fprintf(stderr, "writing to %s\n", p2->call_block[0]);
        break;
        
    case 10: //file > process
        //read p1
        //write to p2 stdin
        fprintf(stderr, "reading from %s", p1->call_block[0]);
        p2->function(p2); 
        break;
        
    case 11: //file > file
        //read p1
        //write to p2
        fprintf(stderr, "reading from %s", p1->call_block[0]);
        fprintf(stderr, "writing to %s", p2->call_block[0]);
        break;
            
    }
}

struct Process*  CmpOperation(struct Process *p1, struct Process *p2, char *op){
    int i = CheckIfFile(p1)*10 + CheckIfFile(p2);

    

}

