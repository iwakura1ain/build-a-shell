
char *CURRENT_DIR = 0;

const int DELIM_LEN = 9;
const char DELIMS[DELIM_LEN] = {'|',    '>', '=', '~', '-',    '&', '!',    '(', ')' };
/*
 a>b : pipe process a to process b
 a=b : pipe process a to file b
 a~b : pipe file a to process b
 a-b : pipe file a to file b

 a|b : if file a or b exists, equals file a or/and b 
 a&b : if process a succeeds, equals process b
 a!b : if process a fails, equals process b

 (a) : run a first  
*/




   





