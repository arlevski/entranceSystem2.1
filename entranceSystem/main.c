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

#define LOG_PATH "log.txt"
/***
 * This is the path where the log file is located.
 * Open this file and append new records into it.
 * When you submit the program make sure this path match to: "c:\\temp\\log.txt"
 ***/


typedef struct S_User
{
    char name[20]; // user name
    char code[8];    // user code
    int permissionStatus;   //user status
    struct S_User *next;
    struct S_User *previous;
    
    //start time
    
    //end time
    
    //pulse
} User;

void PrintList(User *start) {
    User *currentUser = start;
    int count = 0;
    
    User *ahead = NULL;
    User *behind = NULL;
    
    while(currentUser != NULL) {
        count++;
        
        ahead = currentUser->next;
        behind = currentUser->previous;
        
        printf("%-20s %-8s \n",
               currentUser->name,
               currentUser->code,
               (ahead == NULL) ? "None" : ahead->name,
               (behind == NULL) ? "None" : behind->name
               );
        currentUser = currentUser->next;
        ahead = NULL;
        behind = NULL;
    }
    printf("Total Users:%d\n",count);
}

User *AddUser(User *previous) {
    
    printf("Enter Name And Code: ");
    char input[16];
    fgets( input, 15, stdin);
    
    User *newUser = malloc(sizeof(User));
    sscanf(input, "%s %s \n", newUser->name, newUser->code);
    printf("Added:%s Code:%s\n\n",newUser->name, newUser->code);
    
    newUser->next = NULL;
    newUser->previous = NULL;
    
    if(previous != NULL) {
        previous->next = newUser;
        newUser->previous = previous;
    }
    
    return newUser;
}
void CleanUp(User *start) {
    
    User *freeMe = start;
    User *holdMe = NULL;
    while(freeMe != NULL) {
        holdMe = freeMe->next;
        printf("Free Name:%s Code:%s\n",
               freeMe->name,
               freeMe->code);
        free(freeMe);
        freeMe = holdMe;
    }
}

User *ReadNextFromFile(User *start, FILE *pFile) {
    size_t returnValue;
    if(start == NULL) {
        start = malloc(sizeof(User));
        returnValue = fread(start, sizeof(User), 1, pFile);
        start->next = NULL;
        start->previous = NULL;
    } else {
        User *indexUser = start;
        User *newUser = malloc(sizeof(User));
        while(indexUser->next != NULL) {
            indexUser = indexUser->next;
        }
        returnValue = fread(newUser, sizeof(User), 1, pFile);
        indexUser->next = newUser;
        newUser->next = NULL;
        newUser->previous = indexUser;
    }
    return start;
}

User *ReadListIn(User *start) {
    
    FILE *pFile;
    pFile = fopen("/Users/odedarlevski/Documents/Projects/entranceSystem/entranceSystem/test.txt", "r");
    if(pFile != NULL) {
        
        CleanUp(start);
        start = NULL;
        
        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);
        
        int numEntries = (int)(fileSize / (sizeof(User)));
        printf("numEntries:%d\n",numEntries);
        
        int loop = 0;
        for(loop = 0; loop < numEntries; ++loop) {
            fseek(pFile, (sizeof(User) * loop), SEEK_SET);
            start = ReadNextFromFile(start, pFile);
        }
    }  else {
        printf("FILE OPEN ERROR FOR READ\n");
    }
    
    return start;
    
}

void WriteListToFile(User *start) {
    FILE *pFile;
    pFile = fopen("/Users/odedarlevski/Documents/Projects/entranceSystem/entranceSystem/test.txt", "w");
    
    if(pFile != NULL) {
        User *currentUser = start;
        
        User *holdNext = NULL;
        User *holdPrevious = NULL;
        
        while(currentUser != NULL) {
            holdNext = currentUser->next;
            holdPrevious = currentUser->previous;
            
            currentUser->next = NULL;
            currentUser->previous = NULL;
            
            fseek(pFile, 0, SEEK_END);
            fprintf(pFile, "%-20s %-8s \n",
                    currentUser->name, currentUser->code);
            //fwrite(currentUser, sizeof(User), 1, pFile);
            
            printf("Writing:%s to file\n",currentUser->name);
            
            currentUser->next = holdNext;
            currentUser->previous = holdPrevious;
            
            holdNext = NULL;
            holdPrevious = NULL;
            
            currentUser = currentUser->next;
        }
        fclose(pFile);
        pFile = NULL;
    } else {
        printf("FILE OPEN ERROR\n");
    }

}

void readAccess(char *path)
{
    FILE *fp;
    int status, pulse;
    char temp[100], name[21], code[9], date_s[11], date_e[11], time_s[6], time_e[6];
    
    
    fp = fopen( path, "r");
    if (!fp)
    {
        printf("File not found!\n");
        return;
    }
    
    //header
    fgets(temp, 100, fp);
    puts(temp);
    
    
    while (fscanf(fp, "%20s %8s %1d %10s %10s %5s %5s %5d", name, code, &status, date_s, date_e, time_s, time_e, &pulse) != EOF)
    {
        printf("%-20s %-8s %-1d %-10s %-10s %-5s %-5s %-5d\n", name, code, status, date_s, date_e, time_s, time_e, pulse);
        
    }
    
    fclose(fp);
    return;
}


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








int main(int argc, char *argv[]) {
    
    readAccess(ACCESS_PATH);

    char command[16];
    char input[16];
    
    User *start = NULL;
    User *newest = NULL;
    
    
    printf("Please type 'add', 'print' or 'quit'\n");
    while( fgets( input, 15, stdin) ) {
        
        sscanf(input,"%s",command);
        
        if ( strncmp(command, "quit", 4) == 0) {
            printf("\n\nBreaking...\n");
            break;
        } else if ( strncmp(command, "print", 5) == 0) {
            PrintList(start);
        } else if ( strncmp(command, "write", 5) == 0) {
            WriteListToFile(start);
        } else if ( strncmp(command, "read", 4) == 0) {
            start = ReadListIn(start);
        } else if ( strncmp(command, "add", 3) == 0) {
            if(start == NULL) {
                start = AddUser(NULL);
                newest = start;
            } else {
                newest = AddUser(newest);
            }
        }
    }
    
    CleanUp(start);
    return 0;
    
}



