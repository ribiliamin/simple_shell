#include "shell.h"



/*
* screenprint :this function mimicks printf
* @string_2print - string to be printed to stdout
* here i will simply use the std output write function
* another idea is to use echo 
*/

void screenprint(const char *string_2print)
{
    write(STDOUT_FILENO,string_2print,strlen(string_2print));
    

}
