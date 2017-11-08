#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

int main(){
  int temp;
  char* mem;
  temp = open("./temp", O_RDWR);
  mem = (char *) mmap(NULL, sizeof(char)*10, PROT_WRITE|PROT_READ, MAP_SHARED, temp, 0);
  for(int i; i<20; i++){
    printf("Output: %s\n", mem);
    fflush (stdout);
    sleep(2);
  }
}
