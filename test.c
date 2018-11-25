#include <stdio.h>

#include <string.h>

int main ()
{
    char buf[] ="Name varchar,RollNo int";
	const char s1[10] = "' ',','";	
	int i = 0,j = 0;
    char *p1 = strtok (buf, s1);
    char *array1[10];
    
    while (p1 != NULL)
    {
        array1[i++] = p1;
        p1 = strtok (NULL, s1);
        j++;
    }
    for (i = 0; i < j; ++i)  
        printf("%s\n", array1[i]);
    return 0;
}