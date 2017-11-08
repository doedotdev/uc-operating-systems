#include <stdio.h>
#include <stdlib.h> //for atoi
#include <unistd.h> //for fork

void printInfo(int process, int runTimes) {
    for(int i = 0; i < runTimes; i++){
        printf("CHILD (%i): %d : PARENT: %d\n", process, getpid(), getppid());
        sleep(2);
    }
}

void printMain(int runTimes) {
    for(int i = 0; i < runTimes; i++){
        printf("MAIN PROCESS: PID: %d\n", getpid());
        sleep(2);
    }
}

int main(int argc, char **argv)
{

    // convert to int
    char *p;
    int runTimes;

    // check number of arguments coming in
    if (argc - 1 != 1) {
        printf("\n only one argument needed. \n");
        printf("Usage < ./program 4 >\n\n");
        return 0;
    } else {
        runTimes = strtol(argv[1], &p, 10);
    }

    // forks and logic
    pid_t one, two, three;
    one = fork();
    if(one > 0){
        two = fork();
        if(two > 0){
            three = fork();
            if(three > 0){
                printMain(runTimes);
            } else { printInfo(3, runTimes); }
        } else { printInfo(2, runTimes); }
    } else { printInfo(1, runTimes); }
    
  return 0;
}