#include <stdio.h>
#include <dirent.h>
#include <errno.h>

int main()
{
    DIR *dir = opendir("db/munjal");
    if (dir)
    {
        /* Directory exists. */
        printf("Directory exists");
        closedir(dir);
    }
    else if (ENOENT == errno)
    {
        printf("can not find the folder");
        /* Directory does not exist. */
    }
    else
    {
        printf("error with the file");
        /* opendir() failed for some other reason. */
    }
}