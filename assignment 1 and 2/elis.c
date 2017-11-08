#include <stdio.h>
#include <stdlib.h> //for atoi
#include <unistd.h> //for fork

int main(int argc, char **argv)
{

    // check number of arguments coming in
    if (argc - 1 != 1) {
        printf("\n Please supply one and only one argument. \n");
        return 0;
    }

    char* userInput = argv[1];


    if( access(userInput, F_OK ) == -1 ) {
        
        printf("\n Please give a valid file name in this directory");
    } else {
         pid_t childOne, childTwo, childThree;

        //Fork One

        childOne = fork();

        if(childOne > 0){
            //Fork Two
            childTwo = fork();
            if(childTwo > 0){
                //Fork Three
                childThree = fork();
                if(childThree > 0){
                    int returnStatus;
                    //Parent waits until child 3 is done.
                    printf("This is the main process, my PID is %d\n", getpid());
                    waitpid(childTwo, &returnStatus ,0);
                    waitpid(childOne, &returnStatus,0);
                    printf("\nmain process terminates\n");
                }else if(childThree < 0){
                    printf("error\n");
                }else{
                    //do stuff for fork three here
                    printf("\n\n\n");
                    char *const parmList[] = {"cat",userInput ,NULL};
                    execvp("/bin/cat", parmList);
                }
            }else if(childTwo < 0){
                printf("error\n");
            }else{
                //do stuff for fork two here
                printf("\n\n\n");
                char *const parmList[] = {"ps","-ef" ,NULL};
                execvp("/bin/ps", parmList);
            }
        }else if(childOne < 0){
            printf("error\n");
        }else{
            //Do stuff for fork one here
            printf("\n\n\n");
            execl("/bin/ls","ls", "-l", 0);
        }
    }

    
    
  return 0;
}