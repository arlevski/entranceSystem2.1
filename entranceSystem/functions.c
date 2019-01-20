////  Created by Oded Arlevski ID - 203462270
//
//
////#include "functions.h"
//
//
//
//void getDateTime(int *day, int *month, int *year, int *hours, int *mins)
//{
//    time_t rawtime;
//    struct tm *timeinfo;
//    
//    time(&rawtime);
//    timeinfo = localtime( &rawtime);
//    
//    *day = timeinfo->tm_mday;
//    *month = timeinfo->tm_mon + 1;
//    *year = timeinfo->tm_year + 1900;
//    *hours = timeinfo->tm_hour;
//    *mins = timeinfo->tm_min;
//}
//
////void WriteToLog(char *logName, char *comment){
////
////    FILE *pFile;
////    pFile = fopen(LOG_PATH, "a");
////    int day, month, year, hours, mins;
////
////    getDateTime(&day,&month,&year,&hours,&mins);
////
////    fprintf(pFile, "Action: %s ----  Description: %s ---  %02d/%02d/%d, %02d:%02d\n", logName,
////            comment,day,month,year,hours,mins);
////
////
////
////    fclose(pFile);
////
////}
//
//
//User *addUser(User * head, char *name, char *code, int status, char *date_s, char *date_e, char *time_s, char *time_e){
//    
//    User *current = head;
//    User *newUser;
//    User *temp;
//    int added = 0;
//    
//    newUser = (User*)malloc(sizeof(User));
//    strcpy(newUser->name, name);
//    strcpy(newUser->code, code);
//    newUser->status = status;
//    strcpy(newUser->date_s, date_s);
//    strcpy(newUser->date_e, date_e);
//    strcpy(newUser->time_s, time_s);
//    strcpy(newUser->time_e, time_e);
//    
//    while (added == 0) {
//        
//        
//        if (strcmp(current->code, code) > 0) {
//            
//            printf("%s code is %s need to come After the new user %s code(%s) \n", current->name, current->code, name, code );
//            
//            if (current == head) { // if new user code is bigger than the first user in the list
//                
//                newUser->previous = NULL;
//                newUser->next = current;
//                current->previous = newUser;
//                head = newUser;
//            }
//            else if (!current){ // if new user code is the smallest in the list
//                
//                
//            }
//            else{
//                temp = current;
//                newUser->previous = current->previous;
//                newUser->next = current;
//                newUser->previous->next = newUser;
//                
//                current->previous = newUser;
//            }
//            printf("new user: %s has been added, after: %s , before: %s \n", newUser->name,
//                   newUser->previous->name, newUser->next->name);
//            added = 1;
//        }else{
//            if(current->next){
//                current = current->next;
//            }else{
//                newUser->previous = current;
//                newUser->next = NULL;
//                current->next = newUser;
//                added = 1;
//            }
//            
//        }
//        
//        
//    }
//    WriteListToFile(head);
//    return head;
//}
//
//
//
//User *readAccess(char *path , User *head)
//{
//    FILE *fp;
//    int status;
//    char temp[100], name[21], code[9], date_s[11], date_e[11], time_s[6], time_e[6];
//    
//    
//    fp = fopen( path, "r");
//    if (!fp)
//    {
//        printf("File not found!\n");
//        return NULL;
//    }
//    
//    //header
//    fgets(temp, 100, fp);
//    puts(temp);
//    
//    
//    while (fscanf(fp, "%20s %8s %1d %10s %10s %5s %5s", name, code, &status, date_s, date_e, time_s, time_e) != EOF)
//    {
//        
//        User *current = head;
//        if (current != NULL){ // Head is not null.. there is at least one element
//            //printf("not null \n");
//            while (current->next != NULL) {
//                current = current->next;
//            }
//            current->next = (User*)malloc(sizeof(User));
//            current->next->previous = current;
//            current = current->next;
//            
//            strcpy(current->name, name);
//            strcpy(current->code, code);
//            current->status = status;
//            strcpy(current->date_s, date_s);
//            strcpy(current->date_e, date_e);
//            strcpy(current->time_s, time_s);
//            strcpy(current->time_e, time_e);
//            current->next = NULL;
//            
//            
//            //printf("Username: %s \n",current->name );
//        }
//        else // Head is null..
//        {
//            
//            current = (User*)malloc(sizeof(User));
//            
//            
//            strcpy(current->name, name);
//            strcpy(current->code, code);
//            current->status = status;
//            strcpy(current->date_s, date_s);
//            strcpy(current->date_e, date_e);
//            strcpy(current->time_s, time_s);
//            strcpy(current->time_e, time_e);
//            current->next = NULL;
//            current->previous = NULL;
//            
//            head = current;
//            //        printf("null \n");
//            //        printf("Username: %s \n",current->name );
//        }
//        
//        
//        printf("%-20s %-8s %-1d %-10s %-10s %-5s %-5s \n", name, code, status, date_s, date_e, time_s, time_e);
//        
//    }
//    
//    fclose(fp);
//    return head;
//}
//
//
//
//
//
//
//
//
//
//void printList(User *head){
//    
//    User *current = head;
//    
//    
//    printf("Name                 Code     S Start date End date   Stime Etime \n");
//    
//    while (current != NULL) {
//        printf("%-20s %-8s %-1d %-10s %-10s %-5s %-5s \n", current->name, current->code, current->status, current->date_s,
//               current->date_e, current->time_s, current->time_e);
//        current = current->next;
//    }
//    printf("The End \n");
//    
//    // WriteToLog("Print List" , "Print users list");
//    
//}
//
//void WriteListToFile(User *head) {
//    FILE *pFile;
//    pFile = fopen("/Users/odedarlevski/Documents/Projects/entranceSystem/entranceSystem/test.txt", "w");
//    
//    
//    fprintf(pFile, "Name                 Code     S Start date End date   Stime Etime\n");
//    
//    if(pFile != NULL) {
//        User *current = head;
//        
//        User *holdNext = NULL;
//        //User *holdPrevious = NULL;
//        
//        while(current != NULL) {
//            holdNext = current->next;
//            //holdPrevious = current->previous;
//            
//            current->next = NULL;
//            //currentUser->previous = NULL;
//            
//            fseek(pFile, 0, SEEK_END);
//            //            fprintf(pFile, "%-20s %-8s \n",
//            //                    currentUser->name, currentUser->code);
//            fprintf(pFile, "%-20s %-8s %-1d %-10s %-10s %-5s %-5s \n", current->name, current->code, current->status, current->date_s, current->date_e,
//                    current->time_s, current->time_e);
//            //fwrite(currentUser, sizeof(User), 1, pFile);
//            
//            printf("Writing:%s to file\n",current->name);
//            
//            current->next = holdNext;
//            // currentUser->previous = holdPrevious;
//            
//            holdNext = NULL;
//            // holdPrevious = NULL;
//            
//            current = current->next;
//        }
//        fclose(pFile);
//        pFile = NULL;
//    } else {
//        printf("FILE OPEN ERROR\n");
//    }
//    
//    
//    
//}
//
//void CleanUp(User *head) {
//    
//    User *freeMe = head;
//    User *holdMe = NULL;
//    while(freeMe != NULL) {
//        holdMe = freeMe->next;
//        printf("Free Name:%s Code:%s\n",
//               freeMe->name,
//               freeMe->code);
//        free(freeMe);
//        freeMe = holdMe;
//    }
//    
//}
//
//
