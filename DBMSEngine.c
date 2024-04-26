#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char *dbms_type;
    char *substring_fun;
} dbms_substring;

dbms_substring database[]={
        {"DBMS1","substr"},
        {"DBMS2","substring"},
        {"DBMS3","sbstr"},
        {"DBMS4","sub_str"}
    };

char *rebuild_query_with_function(char *query, char *substring_func) 
  { 
    char* resultquery; 
    int i,cnt = 0; 
    char FunctionName_to_Replace[]= "{substringFunction}"; // this will get replaced 
    int NewWorld_Length = strlen(substring_func); 
    int OldWorld_Length = strlen(FunctionName_to_Replace); 

    // Counting the number of times old word occur in the string 
    for (i = 0; query[i] != '\0'; i++) { 
        if (strstr(&query[i], FunctionName_to_Replace) == &query[i]) { 
            cnt++; 
 
            // Jumping to the index after the old word. 
            i += OldWorld_Length - 1; 
        } 
    } 

    // Making new string of enough length 
    resultquery = (char*)malloc(i + cnt * (NewWorld_Length - OldWorld_Length) + 1); 
 
    i = 0; 
    while (*query) { 
        // compare the substring with the result query 
        if (strstr(query, FunctionName_to_Replace) == query) { 
            strcpy(&resultquery[i], substring_func); 
            i += NewWorld_Length; 
            query += OldWorld_Length; 
        } 
        else
            resultquery[i++] = *query++; 
    }  
    resultquery[i] = '\0'; 
    return resultquery; 
}

char *rebuild_query(char *query, char *dbms_type) 
{ 
    if (strcmp(query, "") ==0|| strcmp(dbms_type, "")==0)
    {
         printf("DBMS Type and Query can not be empty.");
        return 0;
    };   
    //Get total no of elements in an array
    int  num_database = sizeof(database)/ sizeof (database[0]); 

    for (int i=0;i<num_database ;i++)
        if (strcmp(database[i].dbms_type, dbms_type )==0)
            {
                // Calling function to replace the appropriate substring function
               return rebuild_query_with_function(query,  database[i].substring_fun);                
            }

  // If given DBMS doesn't exist it array list
  fprintf(stderr, "Unsupported DBMS: %s\n", dbms_type);
  return 0;
}

int main()
{
    char query_def[]  = "select {substringFunction}(columnname, 0 ,4) from tablename";
    char dbms_type[] = "DBMS2";
   
    char *rebuilt_query = rebuild_query(query_def, dbms_type);
    if (rebuilt_query != NULL) 
    {
        printf("Rebuilt query: %s\n", rebuilt_query);
        free(rebuilt_query);  // Deallocate memory
    }
    return 0;
}


  