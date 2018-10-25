#include<stdio.h>
#include<stdarg.h> 

int stringPrint(char string[5], ...) 
{
    va_list valist; 
  
    int i,j; 
  
    va_start(valist, string);
    while(string){
        puts(string);
        string = va_arg(valist, char *);
    }
    va_end(valist); 
    return 0; 
}

int main() 
{
    stringPrint("Aditya", "hello", "Anmol", "create"); 
    return 0; 
}