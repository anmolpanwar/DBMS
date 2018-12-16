#include <stdio.h>
#include <string.h>

#include <dirent.h> //to check if a directory exists.
#include <errno.h>

int main()
{
  char query[40], tableQuery[100];
  char databaseName[15];

  FILE *fp;
  int i = 0, j, id;
  char dbName, folderName[18], path[30] = "db/";
  const char delimiters[10] = "' ',','";
  char *p1;
  char *createParsed[8];

  printf("Enter your query to view, create or select databases: \n");
  fgets(query, 40, stdin);

  // Database creation or selection
  switch (query[0])
  {
  case 'V':
  {
    printf("View sequence initiated \n");
    fp = fopen("db/database.txt", "r");
    dbName = fgetc(fp);
    while (dbName != EOF)
    {
      printf("%c", dbName);
      dbName = fgetc(fp);
    }
    fclose(fp);
    break;
  }
  case 'C':
  {
    printf("Create sequence initiated \n");
    j = 0;
    fp = fopen("db/database.txt", "a");
    for (i = 7; i <= strlen(query); i++)
    {
      fprintf(fp, "%c", query[i]);
      folderName[j] = query[i];
      j++;
    }
    printf("%s", folderName);
    strcat(path, folderName);
    mkdir(path);
    fclose(fp);
    break;
  }
  case 'S':
  {
    printf("SELECT sequence initiated \n");
    j = 0;
    for (i = 7; i <= strlen(query); i++)
    {
      databaseName[j] = query[i];
      j++;
    }
    strcat(path, databaseName);
    printf("%s", path);
    DIR *dir = opendir(path);
    if (dir)
    {
      /* Directory exists. */
      printf("Directory exists\n");
      closedir(dir);
    }
    else if (ENOENT == errno)
    {
      printf("can not find the folder\n");
      /* Directory does not exist. */
    }
    else
    {
      printf("error with the file\n");

      /* opendir() failed for some other reason. */
    }
    printf("Enter your query to Create, Insert or Delete a table: \n");
    fgets(tableQuery, 100, stdin);
    switch (tableQuery[0])
    {
    case 'C':
    {
      printf("Table Create sequence initiated \n");
      p1 = strtok(tableQuery, delimiters);
      while (p1 != NULL)
      {
        createParsed[i++] = p1;
        p1 = strtok(NULL, delimiters);
      }
      printf("%s\n", createParsed[2]); //table-name
      // strcat(path, createParsed[2]);
      // printf("%s", path);
      // strcat(path, "tables.txt");
      // fp = fopen(path, "a");
      // for (i = 7; i <= strlen(query); i++)
      // {
      //   fprintf(fp, "%c", query[i]);
      //   folderName[j] = query[i];
      //   j++;
      // }

      break;
    }
    case 'U':
    {
      printf("Table Update sequence initiated \n");
      break;
    }
    }
    break;
  }
  default:
  {
    printf("Invalid Command");
  }
  }

  // UPDATE, SELECT, DELETE, INSERT, MODIFY, LIMIT, OFFSET

  return 0;
}