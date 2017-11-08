#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <string.h>

#define  NOT_READY -1
#define  READY 0
#define  CLIENT 1
#define  FINISHED 2

struct memStruct {
     int  status;
     char  data;
};

int  main(int  argc, char *argv[])
{
     key_t shared_memory_key;
     int shared_memory_id;
     FILE * txt_file;
     struct memStruct *shared_memory_ptr;
     
     shared_memory_key = ftok(".", 'x');
     //create shared memory, size 1000. store it with shared_memory_id.
     shared_memory_id = shmget(shared_memory_key, 1000, IPC_CREAT | 0666);
     if (shared_memory_id < 0) {
          printf("Error\n");
          exit(1);
     }
     printf("Server: Created shared memory segment\n");
     

     //Then create a pointer to that shared memory segment.
     shared_memory_ptr = (struct memStruct *) shmat(shared_memory_id, NULL, 0);
     if ((int) shared_memory_ptr == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     
     //the server is now ready for the client to write to shared memory.
     shared_memory_ptr->status = READY;

     printf("Start Client in another console/terminal window.\n");
     printf("   gcc -o client client.c\n");
     printf("   ./client read.txt\n");
    
     //server waits until client changes status.
     while(shared_memory_ptr->status != FINISHED){
        while (shared_memory_ptr->status != CLIENT)
            sleep(1);
        
        printf("Server: Shared memory from client found.\n");
        printf("Server: Found shared memory containing: %s\n", &(shared_memory_ptr->data));

        
        txt_file = fopen("write.txt", "ab+");
        printf("Server: Writing new found text in write.txt");

        const char *substring = strstr(&(shared_memory_ptr->data), "STOP!!!");

        if(substring){
            printf("Server: Stop string found! \n");
            size_t len = substring - &(shared_memory_ptr->data);
            char *string2 = malloc(len + 1);
        
            if (string2) {
                memcpy(string2, &(shared_memory_ptr->data), len);
                string2[len] = 0;
        
                fputs(string2, txt_file);
            }
            
            shared_memory_ptr->status = FINISHED;
            fclose(txt_file);
        } else {
            fputs(&(shared_memory_ptr->data), txt_file);
            shared_memory_ptr->status = READY;
        }
    }

     //This will happen to close server once it sees a "STOP"
     shmdt((void *) shared_memory_ptr);
     printf("Server: Detached shared memory\n");
     shmctl(shared_memory_id, IPC_RMID, NULL);
     printf("Server: Removed shared memory\n");
     printf("Server: Done\n");
     exit(0);

     return 0;
}