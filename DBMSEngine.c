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
    char *rebuilt_query="";
    if (query == NULL || dbms_type == NULL) 
    {
         printf("DBMS Type and Query can not be Null.\n");
        return 0;
    }
    else if (strcmp(query, "") ==0|| strcmp(dbms_type, "")==0) 
    {
         printf("DBMS Type and Query can not be empty.\n");
        return 0;
    }
   
    //Get total no of elements in an array
    int  num_database = sizeof(database)/ sizeof (database[0]); 

    for (int i=0;i<num_database ;i++)
        if (strcmp(database[i].dbms_type, dbms_type )==0)
            {
                // Calling function to replace the appropriate substring function
               rebuilt_query= rebuild_query_with_function(query,  database[i].substring_fun);   
                if (rebuilt_query != NULL) 
                {
                    printf("Rebuilt query: %s\n", rebuilt_query);
                    free(rebuilt_query);  // Deallocate memory
                }             
            }

  // If given DBMS doesn't exist it array list
  if(strcmp(rebuilt_query,"")==0)
    printf("Unsupported DBMS: %s\n", dbms_type);
  return 0;
}

int main()
{
    //Test Case 1: Pass proper value to both the parameters
    char *query_def  = "select {substringFunction}(columnname, 0 ,4) from tablename";
    char *dbms_type = "DBMS2";

     rebuild_query(query_def, dbms_type);

     //Test Case 2: Pass query with {substringFunction} to replace at 2 places 
    query_def = "select {substringFunction}(columnname, 0 ,4) from tablename where {substringFunction}(columnname, 0 ,4)='SAS'";
    dbms_type = "DBMS2";
   
    rebuild_query(query_def, dbms_type);

    //Test Case 3: Pass DBMS Type which is not in the list
    query_def  = "select {substringFunction}(columnname, 0 ,4) from tablename";
    dbms_type = "DBMS8";
   
    rebuild_query(query_def, dbms_type);

    //Test Case 4: pass empty value to both the parameters
    query_def  = "";
    dbms_type = "";
   
    rebuild_query(query_def, dbms_type);

     //Test Case 5: pass null value in any one parameters
    query_def  = "select {substringFunction}(columnname, 0 ,4) from tablename";
    dbms_type = NULL;
   
    rebuild_query(query_def, dbms_type);
   
    return 0;
}


  