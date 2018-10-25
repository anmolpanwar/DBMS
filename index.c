#include <stdio.h>
#include <string.h>

int main(){
  char query[40];
  char databaseName[15];

  FILE *fp ;
  int i = 0,j, id;
  char dbName,folderName[18];

  printf("Enter your query to view, create or select databases: \n");
  fgets(query, 40, stdin);

  // Database creation or selection
  switch(query[0]){
    case 'V':{
      printf("View sequence initiated \n");  
      fp = fopen("db/database.txt", "r");
      dbName = fgetc(fp);
      while(dbName != EOF){
        printf("%c", dbName);
        dbName = fgetc(fp);
      }
      fclose(fp);
      break;
    }
    case 'C':{
      printf("Create sequence initiated \n");
      folderName[0] = 'd';
      folderName[1] = 'b';
      folderName[2] = '/';
      j = 3;
      fp = fopen("db/database.txt", "a");
      for(i = 7; i <= strlen(query); i++){
        fprintf(fp,"%c",query[i]);
        folderName[j] = query[i];
        j++;
      }
      printf("%s",folderName);
      mkdir(folderName);
      fclose(fp);
      break;
    }
    case 'S':{
      printf("SELECT sequence initiated \n");

      break;
    }
    default: {
      printf("Invalid Command");
    }
  }

  // UPDATE, SELECT, DELETE, INSERT, MODIFY, LIMIT, OFFSET

  return 0;
}
