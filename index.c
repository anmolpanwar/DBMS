#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <errno.h>

int main()
{
  char query[40], tableQuery[100], path[30] = "db/";
  char databaseName[15];

  FILE *fp;
  int i = 0, j, id;
  char dbName, folderName[18] = {'d', 'b', '/'};
  const char delimiters[10] = "' ',','";
  char *p1, *p2;
  char *createParsed[10], *databaseParsed[5];

  printf("Enter your query to view, create or select databases: \n");
  fgets(query, 40, stdin);

  p1 = strtok(query, delimiters);
  while (p1 != NULL)
  {
    databaseParsed[i++] = p1;
    p1 = strtok(NULL, delimiters);
  }
  printf("%s", databaseParsed[1]); //database-name

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
    j = 3;
    fp = fopen("db/database.txt", "a");
    // for (i = 7; i <= strlen(query); i++)
    // {
    fprintf(fp, "%s", databaseParsed[1]);
    //   folderName[j] = query[i];
    //   j++;
    // }
    strcat(folderName, databaseParsed[2]);
    printf("%s", folderName);
    mkdir(folderName);
    fclose(fp);
    break;
  }
  case 'S':
  {
    printf("SELECT sequence initiated \n");
    printf("Enter your query to Create, Insert or Delete a table: \n");
    fgets(tableQuery, 100, stdin);
    switch (tableQuery[0])
    {
    case 'C':
    {
      printf("Table Create sequence initiated \n");
      p2 = strtok(tableQuery, delimiters);
      i = 0;
      while (p2 != NULL)
      {
        createParsed[i++] = p2;
        p2 = strtok(NULL, delimiters);
      }
      printf("%s\n", createParsed[2]); //table-name

      strcat(path, databaseParsed[1]);
      strcat(path, "tables.txt");
      printf("%s", path);
      fp = fopen(path, "a");


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
