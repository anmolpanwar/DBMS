#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <errno.h>

int main()
{
  char query[40], tableQuery[100], path[30] = "db/";
  char databaseName[15], tableName[15];

  FILE *fp;
  int i = 0, counter = 0, id, n, k = 0;
  char dbName, folderName[18] = {'d', 'b', '/'};
  const char delimiters[10] = "' ',','";
  char *p1, *p2;
  char *createParsed[10], *databaseParsed[5];
  char trash1[30], trash2[30], trash3[30];

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
  strcat(path, databaseName);

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
    fp = fopen("db/database.txt", "a");
    fprintf(fp, "%s", databaseParsed[1]);
    strcat(folderName, databaseParsed[1]);
    printf("%s", folderName);
    mkdir(folderName);
    strcat(folderName, "/values");
    mkdir(folderName);
    fclose(fp);
    break;
  }
  case 'S':
  {
    printf("SELECT sequence initiated \n");
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
      return 0;
    }
    else
    {
      printf("error with the file\n");
      return 0;
      /* opendir() failed for some other reason. */
    }
    printf("Enter your query to Create, Insert or Delete a table: \n");
    fgets(tableQuery, 100, stdin);
    p2 = strtok(tableQuery, delimiters);
    i = 0;
    while (p2 != NULL)
    {
      createParsed[i++] = p2;
      p2 = strtok(NULL, delimiters);
      counter++;
    }
    for (i = 0; i < (strlen(createParsed[2])); i++)
    {
      tableName[i] = createParsed[2][i];
    }
    switch (tableQuery[0])
    {
    case 'C':
    {
      printf("Table Create sequence initiated \n");
      printf("%s\n", createParsed[2]); //table-name
      for (i = 0; i < strlen(path); i++)
      {
        trash1[i] = path[i];
      }
      strcat(trash1, "/tables.txt");
      fp = fopen(trash1, "a");
      fprintf(fp, "%s", createParsed[2]);
      for (i = 0; i < strlen(path); i++)
      {
        trash2[i] = path[i];
      }
      strcat(trash2, "/columns.txt");
      fp = fopen(trash2, "a");
      fprintf(fp, "%s %s", tableName, createParsed[3]);
      strcat(path, "/values/");
      strcat(trash3, tableName);
      strcat(trash3, "_");
      strcat(trash3, createParsed[3]);
      strcat(trash3, ".txt");
      printf("%s", trash3);
      fp = fopen(trash3, "a");
      fclose(fp);
      break;
    }
    case 'I':
    {
      printf("Table Insert sequence initiated \n");
      printf("%s", path);
      for (i = 0; i < strlen(path); i++)
      {
        trash1[i] = path[i];
      }
      strcat(trash1, "/values/");
      strcat(trash1, tableName);
      strcat(trash1, "_");
      strcat(trash1, createParsed[3]);
      strcat(trash1, ".txt");
      fp = fopen(trash1, "a");

      // fprintf(fp, "%s", createParsed[4]);
      n = (counter - 4) / 2;
      for (i = 3; i < n + 3; i++)
      {
        k++;
        printf("Insert value %d into %d column", n + 4 + k, 4 + k);
      }
      fclose(fp);
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

  return 0;
}
