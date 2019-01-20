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

void WriteToLog(char *logName, char *comment){
    
    FILE *pFile;
    pFile = fopen(LOG_PATH, "a");
    int day, month, year, hours, mins;
    
    getDateTime(&day,&month,&year,&hours,&mins);
    
    fprintf(pFile, "Action: %s ----  Description: %s ---  %02d/%02d/%d, %02d:%02d\n", logName,
            comment,day,month,year,hours,mins);
    
    
    
    fclose(pFile);
    
}

//User *addUser(User * head, char *name, char *code, int status, char *date_s, char *date_e, char *time_s, char *time_e){
//
//    User *current = head;
//    if (current != NULL){ // Head is not null.. there is at least one element
//        //printf("not null \n");
//        while (current->next != NULL) {
//            current = current->next;
//        }
//        current->next = (User*)malloc(sizeof(User));
//        current->next->previous = current;
//        current = current->next;
//
//        strcpy(current->name, name);
//        strcpy(current->code, code);
//        current->status = status;
//        strcpy(current->date_s, date_s);
//        strcpy(current->date_e, date_e);
//        strcpy(current->time_s, time_s);
//        strcpy(current->time_e, time_e);
//        current->next = NULL;
//
//
//        //printf("Username: %s \n",current->name );
//    }
//    else // Head is null..
//    {
//
//        current = (User*)malloc(sizeof(User));
//
//
//        strcpy(current->name, name);
//        strcpy(current->code, code);
//        current->status = status;
//        strcpy(current->date_s, date_s);
//        strcpy(current->date_e, date_e);
//        strcpy(current->time_s, time_s);
//        strcpy(current->time_e, time_e);
//        current->next = NULL;
//        current->previous = NULL;
//
//        head = current;
//        //        printf("null \n");
//        //        printf("Username: %s \n",current->name );
//    }
//
//
//    //WriteToLog("User Added" , "A User has been added");
//    return head;
//
//}

User *addUser(User * head, char *name, char *code, int status, char *date_s, char *date_e, char *time_s, char *time_e){
    
    User *current = head;
    User *newUser;
    User *temp;
    int added = 0;
   
    newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->name, name);
    strcpy(newUser->code, code);
    newUser->status = status;
    strcpy(newUser->date_s, date_s);
    strcpy(newUser->date_e, date_e);
    strcpy(newUser->time_s, time_s);
    strcpy(newUser->time_e, time_e);
    
    while (added == 0) {
       
        
            if (strcmp(current->code, code) > 0) {
                
                printf("%s code is %s need to come After the new user %s code(%s) \n", current->name, current->code, name, code );
                
                if (current == head) { // if new user code is bigger than the first user in the list
                   
                    newUser->previous = NULL;
                    newUser->next = current;
                    current->previous = newUser;
                    head = newUser;
                }
                else if (!current){ // if new user code is the smallest in the list
                  
                    
                }
                else{
                    temp = current;
                    newUser->previous = current->previous;
                    newUser->next = current;
                    newUser->previous->next = newUser;
                    
                    current->previous = newUser;
                }
                printf("new user: %s has been added, after: %s , before: %s \n", newUser->name,
                       newUser->previous->name, newUser->next->name);
                added = 1;
            }else{
                if(current->next){
                    current = current->next;
                }else{
                    newUser->previous = current;
                    newUser->next = NULL;
                    current->next = newUser;
                    added = 1;
                }
                
            }
        
        
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
        
        User *current = head;
            if (current != NULL){ // Head is not null.. there is at least one element
                //printf("not null \n");
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = (User*)malloc(sizeof(User));
                current->next->previous = current;
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
                current->previous = NULL;
        
                head = current;
                //        printf("null \n");
                //        printf("Username: %s \n",current->name );
            }
        
        
        printf("%-20s %-8s %-1d %-10s %-10s %-5s %-5s \n", name, code, status, date_s, date_e, time_s, time_e);
        
    }
    
    fclose(fp);
    return head;
}









void printList(User *head){
    
    User *current = head;
    
    
    printf("Name                 Code     S Start date End date   Stime Etime \n");
           
    while (current != NULL) {
        printf("%-20s %-8s %-1d %-10s %-10s %-5s %-5s \n", current->name, current->code, current->status, current->date_s,
               current->date_e, current->time_s, current->time_e);
        current = current->next;
    }
    printf("The End \n");
    
    // WriteToLog("Print List" , "Print users list");
    
}

void WriteListToFile(User *head) {
    FILE *pFile;
    pFile = fopen("/Users/odedarlevski/Documents/Projects/entranceSystem/entranceSystem/test.txt", "w");
    
    
    fprintf(pFile, "Name                 Code     S Start date End date   Stime Etime\n");
    
    if(pFile != NULL) {
        User *current = head;
        
        User *holdNext = NULL;
        //User *holdPrevious = NULL;
        
        while(current != NULL) {
            holdNext = current->next;
            //holdPrevious = current->previous;
            
            current->next = NULL;
            //currentUser->previous = NULL;
            
            fseek(pFile, 0, SEEK_END);
            //            fprintf(pFile, "%-20s %-8s \n",
            //                    currentUser->name, currentUser->code);
            fprintf(pFile, "%-20s %-8s %-1d %-10s %-10s %-5s %-5s \n", current->name, current->code, current->status, current->date_s, current->date_e,
                    current->time_s, current->time_e);
            //fwrite(currentUser, sizeof(User), 1, pFile);
            
            printf("Writing:%s to file\n",current->name);
            
            current->next = holdNext;
           // currentUser->previous = holdPrevious;
            
            holdNext = NULL;
           // holdPrevious = NULL;
            
            current = current->next;
        }
        fclose(pFile);
        pFile = NULL;
    } else {
        printf("FILE OPEN ERROR\n");
    }
    
    //WriteToLog("Database Update" , "The database has been updated");
    
}

void CleanUp(User *head) {
    
    User *freeMe = head;
    User *holdMe = NULL;
    while(freeMe != NULL) {
        holdMe = freeMe->next;
        printf("Free Name:%s Code:%s\n",
               freeMe->name,
               freeMe->code);
        free(freeMe);
        freeMe = holdMe;
    }
    //Write to log.txt
    //WriteToLog("Clean Up" , "Clean Up Completed");
}

/*
 * The following function moves the top item in the linked list
 * to its correct position.  This is similar to insertion sort.
 * The item that was the second item in the list becomes the
 * top item. The list should contain at least 2 items and
 * from the second item on, the list should already be sorted.
 */

User *swap( User *head, User *left )
{
    User *right, *temp;
    
    temp = left;                            // store the left user in a temparory slot
    right = temp->next;                    // right user next point to the left user
    temp->previous->next = right;
    if (right->next) {
        left->next = right->next;
    } else{
        left->next = NULL;
    }
    right->previous = temp->previous;//switch up the left user pointers
    left->previous = right;       //to the right user pointers
    
    
    right->next= temp;                      //switch up the right user pointers
           //to the temp slot user pointers
    
    
    
    
    
    
    return head;
}


User *bubbleSort( User *head )
{
    
    User current;
    User temp;
    int swapped;
    
    if( head == NULL ) return NULL;
    do {
        
        swapped = 0;
        current = *head;
        
        while (current.next) // loop on all the list until last user
        {
            printf("current user: %s \n", current.name);
            
            if(strcmp(current.code, current.next->code) > 0) // check if the left user's code is bigger then the right user's code
            {
                printf("%s needs to go right and %s needs to go left \n", current.name,current.next->name);
                temp = current;
                
                while (temp.next) // loop until temp is the last user in the list
                {
                    if(strcmp(temp.code, temp.next->code) > 0) // check if the left user's code is bigger then the right user's code
                    {
                        head = swap(head, &temp);
                        swapped = 1;
                    }
                }
            
            }else{
                current = *current.next;
            }
        }
    } while (swapped);
    
    return head;
}



//User *swapUsers (User *head, User *leftUser, User *rightUser)
//{
//    User temp = *leftUser;
//    if(rightUser->next == NULL){
//        leftUser->next = NULL;
//    }else{
//        leftUser->next = rightUser->next;
//    }
//    leftUser->previous = rightUser;
//
//    rightUser->next = &temp;
//    rightUser->previous = temp.previous;
//    temp.previous->next = rightUser;
//
//    printf("left prev is : %s \n", leftUser->previous);
//
//
//
//
////    leftUser->next = rightUser->next;
////    rightUser->next = &temp;
////
////
////    printf("left prev is : %s \n", leftUser->previous);
////    if(leftUser->previous != NULL)
////    {
////        leftUser->previous->next = rightUser;
////        rightUser->previous = temp.next;
////        leftUser->previous = rightUser;
////    }else{
////        rightUser->previous = temp.next;
////        leftUser->previous = rightUser;
////        head = rightUser;
////    }
//
//
//
//
//    return head;
//
//}
//
//// A function to implement bubble sort
//void bubbleSort(User *head)
//{
//    int swapped;
//    User *ptr1;
//    User *lptr = NULL;
//
//    /* Checking for empty list */
//    if (head == NULL)
//        return;
//
//    while (swapped) {
//
//        swapped = 0;
//        ptr1 = head;
//
//        while (ptr1->next != NULL)
//        {
//            if (strcmp(ptr1->code, ptr1->next->code) > 0)
//            {
//                head = swapUsers(head, ptr1, ptr1->next);
//                swapped = 1;
//
//            }
//        lptr = ptr1;
//        }
//
//    }
//}

//User *bubbleSort(User *head)
//{
//
//    User *current;
//    User *temp;
//
//
//    /* Checking for empty list */
//    if (head == NULL){
//        return head;
//    }
//
//    current = head;
//
//    do {        //do while current is not the last node
//        temp = current;
//
//
//        if (strcmp(temp->code, temp->next->code) > 0) {
//
//            do {
//                 swapUsers(head, temp, temp->next);
//
//            } while (temp->next != NULL);
//
//        }
//
//        printf("current name: %s \n", current->name);
//       current = current->next;
//
//    } while (current !=NULL);
//
//    return head;
//}






///* function to swap data of two nodes a and b*/
//void swap(User *a, User *b)
//{
////    User tempNext = *b->previous;
////    User tempPrev = *a->previous;
////    a->next = b->next;
////    a->previous = b;
////    b->next = &tempNext;
////    b->previous = &tempPrev;
//
//    //User tempNext = *a->next;
////    User tempPrev = *a->previous;
////
////    a->next = b->next;
////    a->previous = b;
////
////    b->next = a;
////    b->previous = &tempPrev;
////    tempPrev.next = b;
//
//
////    User temp = *a;
////    a = b;
////    a->previous = temp.previous;
////
////    b = &temp;
////    b->next = a->next;
////    b->previous = a;
////    a->next = b;
//
////    (&temp)->previous->next = a;
//
//
//    User *before, *after;
//
//    before = a->previous;
//    after = a->next;
//    a->next = after->next;
//    if(before != NULL){
//        before->next = after;
//    }
//    b->next = after->next;
//    a->previous = before;
//    b->next = a;
//    b->previous = before;
//    a->previous = b;
//
//
//}
//
//
//void bubbleSort(User *head)
//{
//    int swapped;
//    User *current;
//    User *last = NULL;
//
//    /* Checking for empty list */
//    if (head == NULL)
//        return;
//
//    do
//    {
//        swapped = 0;
//        current = head;
//
//        while (current->next != last)
//        {
//            if (strcmp(current->code, current->next->code) > 0 )
//            {
//                printf("%s is less than %s\n",current->code ,current->next->code);
//                swap(current, current->next);
//
//                swapped = 1;
//            }
//            else if (strcmp(current->code, current->next->code) < 0 )
//            {
//                printf("%s is more than %s\n",current->code ,current->next->code);
//                //                swap(current, current->next);
//                swapped = 0;
//                current = current->next;
//            }
//
//        }
//        tail = current;
//    }
//    while (swapped);
//}






#endif /* functions_h */
