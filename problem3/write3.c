#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
  int out, length, process_id, temp;
  char* mem;
  temp = open("./temp", O_RDWR);
  process_id = getpid()%10;
  out = process_id;
  length = snprintf(NULL, 0, "%d", out);
  char* str = malloc( length + 1 );
  snprintf( str, length + 1, "%d", out);
  int sz = sizeof(str)*10;
  mem = (char *) mmap(NULL, sz, PROT_WRITE|PROT_READ, MAP_SHARED, temp, 0);
  for(int x = 0; x<20; x++){
    for(int y = 0; y<10; y++)
    {
      *(mem+y)=*str;
    }
    sleep(2);
  }
}
