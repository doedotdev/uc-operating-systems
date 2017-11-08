#include <stdio.h>
#include <stdlib.h> //for atoi
#include <unistd.h> //for fork

void printInfo(int process) {
        printf("CHILD (%i): %d : PARENT: %d\n", process, getpid(), getppid());
}

void printMain() {
        printf("MAIN PROCESS: PID: %d\n", getpid());
        printf("Now waiting for child process to die. . .");
}

int main(int argc, char **argv)
{

    if( access( argv[1], F_OK ) != -1 ) {
        printf("File %s exists in current directory.\n", argv[1]);
    } else {
        printf("File %s does not exist in current directory.\n", argv[1]);
        printf("Please specify a single file in current directory.\n");
        return 0;
    }

    // forks and logic
    pid_t one, two, three;
    one = fork();
    if(one > 0){
        two = fork();
        if(two > 0){
            three = fork();
            if(three > 0){ // main
                printMain();
                waitpid(two, 0 , 0); // wait for process 2 to finish
                waitpid(one, 0 , 0); // wait for process 1 to finish.
                printf("Main Process is Terminated.");
            } else { // ps
                execl("/bin/ps", "ps", "-ef", 0);
            }
        } else { // ls
            execl("/bin/ls", "li", "-l", 0); 
        }
    } else { // cat
        execl("/bin/cat","cat", argv[1], 0);
    }
  return 0;
}