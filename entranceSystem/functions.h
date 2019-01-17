//  Created by Oded Arlevski ID - 203462270

#ifndef functions_h
#define functions_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


#define ACCESS_PATH "/Users/odedarlevski/Documents/Projects/entranceSystem/entranceSystem/access.txt"
/***
 * This is the path where the access file is located.
 * When you submit the program make sure this path match to: "c:\\temp\\access.txt"
 ***/

#define LOG_PATH "/Users/odedarlevski/Documents/Projects/entranceSystem/entranceSystem/log.txt"
/***
 * This is the path where the log file is located.
 * Open this file and append new records into it.
 * When you submit the program make sure this path match to: "c:\\temp\\log.txt"
 ***/


typedef struct S_User
{
    char name[20];          // user name
    char code[8];           // user code
    int status;             // user status
    char date_s[11];        // Start date
    char date_e[11];        // End date
    char time_s[6];         // start time
    char time_e[6];         //end time
    
    struct S_User *next;
    struct S_User *previous;
    
} User;


void getDateTime(int *day, int *month, int *year, int *hours, int *mins)
{
    time_t rawtime;
    struct tm *timeinfo;
    
    time(&rawtime);
    timeinfo = localtime( &rawtime);
    
    *day = timeinfo->tm_mday;
    *month = timeinfo->tm_mon + 1;
    *year = timeinfo->tm_year + 1900;
    *hours = timeinfo->tm_hour;
    *mins = timeinfo->tm_min;
}

User *addUser(User * head, char *name, char *code, int status, char *date_s, char *date_e, char *time_s, char *time_e){
    
    User *current = head;
    if (current != NULL){ // Head is not null.. there is at least one element
        //printf("not null \n");
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = (User*)malloc(sizeof(User));
        current = current->next;
        
        strcpy(current->name, name);
        strcpy(current->code, code);
        current->status = status;
        strcpy(current->date_s, date_s);
        strcpy(current->date_e, date_e);
        strcpy(current->time_s, time_s);
        strcpy(current->time_e, time_e);
        current->next = NULL;
        
        //printf("Username: %s \n",current->name );
    }
    else // Head is null..
    {
        
        current = (User*)malloc(sizeof(User));
        
        
        strcpy(current->name, name);
        strcpy(current->code, code);
        current->status = status;
        strcpy(current->date_s, date_s);
        strcpy(current->date_e, date_e);
        strcpy(current->time_s, time_s);
        strcpy(current->time_e, time_e);
        current->next = NULL;
        
        head = current;
        //        printf("null \n");
        //        printf("Username: %s \n",current->name );
    }
    return head;
}

User *readAccess(char *path , User *head)
{
    FILE *fp;
    int status;
    char temp[100], name[21], code[9], date_s[11], date_e[11], time_s[6], time_e[6];
    
    
    fp = fopen( path, "r");
    if (!fp)
    {
        printf("File not found!\n");
        return NULL;
    }
    
    //header
    fgets(temp, 100, fp);
    puts(temp);
    
    
    while (fscanf(fp, "%20s %8s %1d %10s %10s %5s %5s", name, code, &status, date_s, date_e, time_s, time_e) != EOF)
    {
//        User *current = head;
//        if (current != NULL){ // Head is not null.. there is at least one element
//            printf("not null \n");
//            while (current->next != NULL) {
//                current = current->next;
//            }
//            current->next = (User*)malloc(sizeof(User));
//            current = current->next;
//            strcpy(current->name, name);
//            current->next = NULL;
//            printf("Username: %s \n",current->name );
//        }
//        else // Head is null..
//        {
//        /* now we can add a new variable */
//        current = (User*)malloc(sizeof(User));
//        //current = current->next;
//        strcpy(current->name, name);
//        current->next = NULL;
//        head = current;
//            printf("null \n");
//            printf("Username: %s \n",current->name );
//        }
       // User *current = head;
        head = addUser(head, name, code, status, date_s, date_e, time_s, time_e);
        printf("%-20s %-8s %-1d %-10s %-10s %-5s %-5s \n", name, code, status, date_s, date_e, time_s, time_e);
        
    }
    
    fclose(fp);
    return head;
}









void printList(User *head){
    
    User *current = head;
    
    while (current != NULL) {
        printf("%-20s %-8s %-1d %-10s %-10s %-5s %-5s \n", current->name, current->code, current->status, current->date_s,
               current->date_e, current->time_s, current->time_e);
        current = current->next;
    }
    printf("The End \n");
    
    
    
    
    
}





#endif /* functions_h */
