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
  char trash1[30], trash2[30];

  printf("Enter your query to view, create or select databases: \n");
  fgets(query, 40, stdin);

  p1 = strtok(query, delimiters);
  while (p1 != NULL)
  {
    databaseParsed[i++] = p1;
    p1 = strtok(NULL, delimiters);
  }
  printf("%s", databaseParsed[1]); //database-name
  for (i = 0; i < (strlen(databaseParsed[1]) - 1); i++)
  {
    databaseName[i] = databaseParsed[1][i];
  }

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
      strcat(path, databaseName);
      for (i = 0; i < strlen(path); i++)
      {
        trash1[i] = path[i];
      }
      strcat(trash1, "/tables.txt");
      printf("%s", trash1);
      fp = fopen(trash1, "a");
      fprintf(fp, "%s", createParsed[2]);

      for (i = 0; i < strlen(path); i++)
      {
        trash2[i] = path[i];
      }
      strcat(trash2, "/columns.txt");
      printf("%s", trash2);
      fp = fopen(trash2, "a");
      fprintf(fp, "%s %s", createParsed[2], createParsed[3]);

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
