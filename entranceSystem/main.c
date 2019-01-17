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
    
    
    head = readAccess(ACCESS_PATH, head);
    
    
    do  {
        
        printf("Please Choose Your Action: \n");
        fgets(action,10,stdin);
    
        if ( strncmp( action, "quit", 4) == 0) {
            printf("\n\nBreaking...\n");
            break;
        }
        if ( strncmp( action, "add", 3) == 0){
            
            printf("Add User Details: \n");
            
            printf("Name:");
            //fgets(name,21,stdin);
            scanf("%s", name);
            
            printf("Access Code: ");
            //fgets(code,8,stdin);
            scanf("%s", code);
            
            
            printf("Permission Status: ");
            scanf("%d", &status);
            
//            fgets(&statusChar,1,stdin);
//            status =  atoi(&statusChar);
//
           
            printf("Start Date: ");
            //fgets(date_s,11,stdin);
            scanf("%s", date_s);

            printf("End Date: ");
            scanf("%s", date_e);
           // fgets(date_e,11,stdin);

            printf("Start Time: ");
            scanf("%s", time_s);
            //fgets(time_s,6,stdin);

            printf("End Time: ");
            scanf("%s", time_e);
            //fgets(time_e,6,stdin);

            
            
            head = addUser(head, name, code, status, date_s, date_e, time_s, time_e);
            
            
            
            //head = addUser(head, name, status);
            
           
            
        }if ( strncmp( action, "print", 5) == 0) {
            printList(head);
        }if ( strncmp( action, "write", 5) == 0) {
            WriteListToFile(head);
        }else{
            printf("Input Not Valid.... \n");
        }
        
    
    }while (1);
    
    
    
//    char command[15];
//    char input[15];
//
//    User *start = NULL;
//    User *newest = NULL;
//

    

//    printf("Please type 'add', 'print' or 'quit'\n");
//    while( fgets( input, 15, stdin) ) {
//
//        sscanf(input,"%s",command);
//
//        if ( strncmp(command, "quit", 4) == 0) {
//            printf("\n\nBreaking...\n");
//            break;
//        } else if ( strncmp(command, "print", 5) == 0) {
//            PrintList(start);
//        } else if ( strncmp(command, "write", 5) == 0) {
//            WriteListToFile(start);
//        } else if ( strncmp(command, "read", 4) == 0) {
//            start = ReadListIn();
//
//        } else if ( strncmp(command, "add", 3) == 0) {
//            if(start == NULL) {
//                start = AddUser(NULL);
//                newest = start;
//            } else {
//                newest = AddUser(newest);
//            }
//        }
//    }
//
    CleanUp(head);
    return 0;
   
}



