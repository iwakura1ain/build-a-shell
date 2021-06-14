#ifndef POSTFIX_PARSER
#define POSTFIX_PARSER
#include "postfix_parser.h"
#endif

#ifndef TOKEN_PARSER
#define TOKEN_PARSER
#include "token_parser.h"
#endif

#ifndef EXECUTE
#define EXECUTE
#include "execute.h"
#endif

/*
int IsOperator(char *op){
    int i, j;
    for(i=0; i<(int)strlen(op); i++){
        for(j=0; j<DELIM_LEN; j++){
            if(op[i] == DELIMS[j])
                return j;
        }
    }
    
    return -1;

}
*/

int IsOperator(char *token){
    int i, index=-1;

    for(i=0; i<DELIM_LEN; i++){
        if(token[0] == DELIMS[i]){  //if token is an operator, it will always be len=2
            index = i;
            break;
        }
    }

    return index;    
}

int OpPrecedence(int op_index){
    switch(op_index){
    case 2:   //'>', '=', '~', '-' has same precedence
        return op_index-1; 
    case 3:  
        return op_index-2;
    case 4:
        return op_index-3;


    case 6:  //'&', '!' has same precedence
        return op_index-1; 
        
    default:
        return op_index;
    }
}

//if minus, must pop preceding op from stack then push
//if plus|zero, just push (or stack is empty) 
int GetPrecedence(char *op1, struct Stack *stack){ 
    int i = OpPrecedence(IsOperator(op1));
    int j = OpPrecedence(IsOperator(Peek_Stack(stack)));

    if(stack->len == 0)  //stack empty
        return 0;
    else        
        return j - i;
}
    
/*
    // '<', '>' has equal precedence...
    if((IsOperator(op1)==2 && precedence==1) || (IsOperator(op1)==3 && precedence==-1)) 
        return 0;
    else
        return precedence;

        *
}

*/
void Push_Stack(char *op, struct Stack *Operators){
    //if(Operators.top >= 50)  //shitty attempt at overflow protection
    //  return;
    
    Operators->Stack[Operators->top] = op;
    Operators->top++;
    Operators->len++;
}

char* Pop_Stack(struct Stack *Operators){
    char* pop_value = NULL;
    int pop_index = Operators->top;

    if(pop_index -1 < 0)
        return pop_value;
    else{
        pop_value = Operators->Stack[pop_index -1];
        Operators->Stack[pop_index -1] = NULL;
        
        Operators->top--;
        Operators->len--;
        
        return pop_value;
    }
}

char* Peek_Stack(struct Stack *Operators){
    return Operators->Stack[Operators->top-1];
}

void Push_Queue(char *block, struct Queue *Block){
    int i;

    /*
    if( (Block->push_index <= 0 && Block->pop_index >= 49) || (Block->push_index > Block->pop_index) ) //shitty attempt at overflow prevention
        return;
    */
    
    if(Block->push_index <= 0 && Block->pop_index+5 < 50){ //no space to push on queue
        //TODO: implement realloc of queue
        for(i=Block->pop_index; i >= Block->push_index; i--){  //MAKE SPACE!
            Block->Queue[i+5] = Block->Queue[i];
        }

        for(i=1; i<4; i++)  //cleanup of shifted items
            Block->Queue[Block->push_index +i] = NULL;
            
        Block->push_index += 5;
        Block->pop_index += 5;

    }
    else if(Block->pop_index > 45) //cannot be shifted
        return;

    Block->Queue[Block->push_index] = block;
    Block->push_index--;
    Block->len++;
}

char* Pop_Queue(struct Queue *Block){
    char *pop_value = NULL;

    if(Block->pop_index >= 50){ //no space left on queue
        //TODO: implement realloc of queue
        return pop_value;
    }
    else if(Block->len == 0)  //nothing in queue
        return pop_value;
            
    else{
        pop_value = Block->Queue[Block->pop_index];
        Block->Queue[Block->pop_index] = NULL;
        Block->pop_index--;
        Block->len--;
        
        return pop_value;
    }
}

void PostfixSorter(struct Tokens *tokens){
    struct Stack stack = {.Stack={NULL}, .top=0, .len=0};
    struct Queue queue = {.Queue={NULL}, .push_index=25, .pop_index=25, .len=0};
    
    char *token=NULL;
    int op_precedence;
    int i;

    //for(i=0; i<tokens->token_count; i++)
    //    printf("\n%s", tokens->token_array[i]);

    for(i=0; i<tokens->token_count; i++){
        token = tokens->token_array[i];
        op_precedence = IsOperator(token);
        
        if(op_precedence >= 0){  //is operator
            if(op_precedence == IsOperator(")")){  //closing ')'
                while( IsOperator(Peek_Stack(&stack)) != IsOperator("(") ){ //pop operators until is '(' found
                    Push_Queue(Pop_Stack(&stack), &queue);
                }
                Pop_Stack(&stack); //discard opening '('

                continue;
            }
            else if(op_precedence == IsOperator("(")){ //opening '('
                Push_Stack(token, &stack);
                continue;
            }
            else{
                if(GetPrecedence(token, &stack) > 0){ //precedence is lower|same, thus only needs to push
                    Push_Stack(token, &stack);
                    continue;
                }
                else{ //precedence is higher, so must pop operators first
                    while( GetPrecedence(token, &stack) < 0){
                        Push_Queue(Pop_Stack(&stack), &queue);
                    }
                    Push_Stack(token, &stack); //push current token into operator stack
                    continue;
                }
            }
        }
        else{ //is token block
            Push_Queue(token, &queue); //push token block into queue
        }
            
    }

    if(stack.len != 0){
        for(i=0; i<=stack.len; i++)  //pop entire leftover operator stack to block queue
            Push_Queue(Pop_Stack(&stack), &queue);
    }

    
    if(!PostfixCheck(tokens)){  //check for operator syntax error
        i=0;
        while(queue.len > 0){  //copy sorted tokens into array for return
            tokens->postfix_array[i] = Pop_Queue(&queue);
            i++;
        }
        tokens->token_count = i;
        return;
    }
    else{
        fprintf(stderr, "operator syntax error");
        tokens->token_count = 0;
        return;
    }
        
}

int PostfixCheck(struct Tokens *tokens){    
    int i=0, block_count=0;

    for(i=0; i<tokens->token_count; i++){
        if(IsOperator(tokens->postfix_array[i]) < 0)
           block_count++;
    }

    if(2*block_count-1 == tokens->token_count)
        return 1;
    else
        return 0;

}
