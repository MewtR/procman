#include <stdio.h>
#include <sys/types.h> // for pid_t, see man pid_t
#include <stdlib.h> // for strtoul, see man strtoul

#include "pids.h"

#define LEN 16

int main(int argc, char * argv[]) 
{
    if (argc < 2){
        printf("Please specify a process \n");
        return -1;
    }
    int i = 0;
    // argv ends with null pointer. So we can end the for loop when that
    // is met
    for(char** av = argv; *av; av++){  
        if(i == 0){
            printf("The program name is: %s \n", argv[0]);
        }else{
            printf("Argument %d is: %s \n", i, *av);
        }
        i++;
    }

    char command_string[LEN];
    char command_result[LEN];
    snprintf(command_string, LEN, "pidof %s", argv[1]);
    FILE *command = popen(command_string, "r");  
    fgets(command_result, sizeof( command_result ), command);
    char * end = command_result+3; // only get the first pid (not a very good way to do it)
    pid_t pid = strtoul(command_result, &end, 10);

    printf("Process id of %s is %i", argv[1], pid);
}

