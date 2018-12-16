# Algorithm
Steps to take care of: 

- [Parse the input](#tokenization)
- Filter the input for SELECT, UPDATE, DELETE
- Make logic to Create a Database
- SELECT a Database
    * [Check if the folder exists](#directory-check)
- [Overview of the file structure](#file-structure)
- Creating a Table
  * Limitations of cloumns - 2
  * Limitations of data types - (int or varchar)
  * Primary Keys and Foreign Keys
- UPDATE a table 
  * Searching for the entry
  * Updating the entry  

## Parse the input

Taking the input in a string, we assume that the string is maximum of length 40. 
```c
char query[40];
fgets(query, 40, stdin);
```
## Parsing the query to SELECT, VIEW, CREATE a database. 
View, Select, Delete all have different first letters. So we can filter them based on the first letter of the query itself. 

- View command just prints the contents of the file database.txt inside the db directory as it is. 

    `Syntax: View (or) VIEW`
- Create command should create the database folder inside the db folder and append the name of the database into the database.txt

    `Syntax: Create <db-name> (or) CREATE <db-name>`

~~Hurdle1: Creating a directory in C.~~
```c
    int folder;
    char* name = "<folder-name>";
    folder = mkdir(name);
```

- Select command should select the default database and ask for the Query to be executed on the database. 

    `Syntax: Select <db-name> (or) SELECT <db-name>`

    The entered query should be parsed again to execute the required command on the selected database.
### (...) Operator
Variable length arguments can be passed using the triple dot operator in C.
```c
#include<stdarg.h> 

int average(int num, ...) 
{ 
    va_list valist; 
  
    int sum = 0, i; 
  
    va_start(valist, num); 
    for (i = 0; i < num; i++)  
        sum += va_arg(valist, int); 
  
    va_end(valist); 
  
    return sum / num; 
}

int main() 
{
    printf("Average of {2, 3, 4} = %d\n", 
    average(2, 3, 4)); 
    printf("Average of {3, 5, 10, 15} = %d\n", 
    average(3, 5, 10, 15)); 
    return 0; 
}
```
Updated version of the code made to divide strings to create table's.
```c
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
```
#### Tokenization 
Dividing the string based on a delimiter. 
```c
#include<string.h>

int main(void)
{
   char str[45] = "Bird!Bird!Bird!The bird is the word!";
   char *substr = NULL;
   /*"Initializes" strtok and gets the first substring*/
   substr = strtok(str," !");
   /*Loops until there are no more substrings*/
   while(substr!=NULL)
   {
       /*Prints the token*/
       puts(substr);
       /*Gets the next substrings*/
       substr = strtok(NULL," !");
   }
   puts("\nWhat remained from the primary string: ");
   puts(str);
   return 0;
}
/*Output:
Bird
Bird
Bird
The
bird
is
the
word

What remained from the primary string:
Bird
 */
```
### CREATE command on a database
After dividing the entered query into subparts using the dilimiter, we call a function which creates the folders on table names and enters the information into their respective `values.txt`.

### File Structure
```bash
[ 
  '|-- db',
  '    |-- database.txt',
  '    |-- <db-name>',
  '        |-- tables.txt',
  '        |-- <table-name>',
  '            |-- columns.txt',
  '            |-- <column-name>',
  '                |-- values.txt',
]
```
-- Minor presentation done -- 
#### Scope of the project: 

- Being able to have it centralised in a way so that multiple users can access it at the same time. 
- Implementing Cloud instance once the above step is done.
- Have options to perform multiple nested queries in a single command.

## Parsing the query to CREATE, SELECT, INSERT, UPDATE, DELETE a table. 

-   Parse this kind of query to ~~dynamically allocate memory~~ create the respective columns in columns.txt after creating the `<table-name>` folder.
    ```c
    CREATE TABLE `auction` (
    `ID` int(11) NOT NULL,
    `Name` varchar(30) NOT NULL,
    `base-price` int(11) NOT NULL,
    `category` varchar(20) NOT NULL
    )
    ```
    Create the folder inside the respective database with the name of the table. 

    ~~Create a `values.txt` file inside each table which contains table names in the first row and values in the corresponding rows.~~

    ```c
    #include <stdio.h>
    #include <string.h>

    int main ()
    {
        char buf[] ="Name varchar,RollNo int";
        const char s1[25] = "' ',','";
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
    ```
    With the restriction that every table should have only 2 attributes, we can divide after every 2 words after the initial 3 words. 

## Directory Check
When we select a database, we need to check if a folder with the same name as the database exists. 
```c
#include <dirent.h>
#include <errno.h>

DIR* dir = opendir("mydir");
if (dir)
{
    /* Directory exists. */
    closedir(dir);
}
else if (ENOENT == errno)
{
    /* Directory does not exist. */
}
else
{
    /* opendir() failed for some other reason. */
}
```