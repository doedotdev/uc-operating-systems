#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/times.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>


int main() {
    int i;
    int n = 6;
    
    for(i=0; i<4; i++){
        n++;
        fork();
    }
    n++;
    printf("n = %d\n", n); 
wait(NULL);
    return 0;
}

