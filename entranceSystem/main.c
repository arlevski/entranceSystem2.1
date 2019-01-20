//  Created by Oded Arlevski ID - 203462270

#include "functions.h"


int main(int argc, char *argv[]) {
    
    
    char action[10];
    char name[21];          // user name
    char code[8];           // user code
    //char statusChar = '\0';
    int status = 0;             // user status
    char date_s[11];        // Start date
    char date_e[11];        // End date
    char time_s[6];         // start time
    char time_e[6];         //end time

    
    User *head = NULL;
    User *current = NULL;
    
    head = readAccess(ACCESS_PATH, head);
    
    printf("\n\n\n------Welcome to 'Oded Enterprises' entrance system------\n\n\n");
    do  {
        
        printf("Please Choose Your Action: \n-add \n-print \n-search \n-update \n-quit \nType One of the Above: ");
        scanf("%s", action);
    
        if ( strncmp( action, "quit", 4) == 0) {
            printf("\n\nBreaking...\n");
            break;
        }
        if ( strncmp( action, "add", 3) == 0){
            
            printf("Add User Details: \n");
            
            printf("Name:");
            scanf("%s", name);
            
            printf("Access Code: ");
            scanf("%s", code);
            
            
            printf("Permission Status: ");
            scanf("%d", &status);
           
            printf("Start Date: ");
            scanf("%s", date_s);

            printf("End Date: ");
            scanf("%s", date_e);

            printf("Start Time: ");
            scanf("%s", time_s);

            printf("End Time: ");
            scanf("%s", time_e);
            
            head = addUser(head, name, code, status, date_s, date_e, time_s, time_e);
            
            
        }
        if ( strncmp( action, "print", 5) == 0) {
            printList(head);
        }
        if ( strncmp( action, "search", 6) == 0) {
            
            do {
                
                printf("By Which Parameter You Want To Search? \n-name \n-status \n-quit \nType One of the Above: ");
                scanf("%s", action);
                if ( strncmp( action, "name", 4) == 0) {
                    printf("Choose name : \n");
                    scanf("%s", name);
                    searchUserByName(head, name);
                    
                }
                if ( strncmp( action, "status", 6) == 0) {
                    printf("Type status from 1 to 5: \n");
                    scanf("%d", &status);
                    searchUserByStatus(head,status);
                    
                }
                if ( strncmp( action, "quit", 4) == 0) {
                    break;
                }

            }while (1);
            
        }
        if ( strncmp( action, "update", 6) == 0) {
            
            do {
                printList(head);
                printf("Choose name from the list above or type 'quit' to go back: \n");
                scanf("%s", name);
                if ( strncmp( name, "quit", 4) == 0) {
                    break;
                }
                current = searchUserByName(head, name);
                printf("Please choose which parameter you want to change: \n-status\n-hours \n-dates \n-quit \nType One of the Above:  ");
                scanf("%s", action);
                if ( strncmp( action, "status", 4) == 0) {
//                    printList(head);
//                    printf("Choose name from the list above: \n");
//                    scanf("%s", name);
//                    current = searchUserByName(head, name);
                    printf("Choose new status (1-5): \n");
                    scanf("%d", &status);
                    current->status = status;
                    printf("------User's status has been updated:------ \n");
                    searchUserByName(head, name);
                    printf("------------\n\n\n\n");
                }
                if ( strncmp( action, "hours", 6) == 0) {
//                    printList(head);
//                    printf("Choose name from the list above: \n");
//                    scanf("%s", name);
//                    current = searchUserByName(head, name);
                    printf("New start time: ");
                    scanf("%s", time_s);
                    printf("New end time: ");
                    scanf("%s", time_e);
                    strcpy(current->time_s, time_s);
                    strcpy(current->time_e, time_e);
                    printf("------User's entry hours has been updated:------ \n");
                    searchUserByName(head, name);
                    printf("------------\n\n\n\n");
                    
                }
                if ( strncmp( action, "dates", 6) == 0) {
//                    printList(head);
//                    printf("Choose name from the list above: \n");
//                    scanf("%s", name);
//                    current = searchUserByName(head, name);
                    printf("New start date: ");
                    scanf("%s", date_s);
                    printf("New end date: ");
                    scanf("%s", date_e);
                    strcpy(current->date_s, date_s);
                    strcpy(current->date_e, date_e);
                    printf("------User's entry dates has been updated:------ \n");
                    searchUserByName(head, name);
                    printf("------------\n\n\n\n");
                    
                }
                if ( strncmp( action, "quit", 4) == 0) {
                    break;
                }
                WriteListToFile(head);
                
            }while (1);
        }
//        else{
//            printf("Input Not Valid.... \n");
//        }
        
    
    }while (1);
    
    
    
    CleanUp(head);
    return 0;
   
}



