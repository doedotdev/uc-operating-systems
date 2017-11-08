#include  <stdio.h>
#include  <stdlib.h>
#include <unistd.h> 
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

#define  NOT_READY -1
#define  READY 0
#define  CLIENT 1
#define  FINISHED 2

struct memStruct {
     int  status;
     char  data;
};

int  main(int argc, char **argv)
{
     key_t shared_memory_key;
     int shared_memory_id;
     struct memStruct  *shared_memory_ptr;
     FILE * text_file;

     if (argc - 1 != 1) {
        printf("\n Give and only one argument. \n");
        printf("   gcc -o client client.c");
        printf("   ./client read.txt");
        return 0;
    }

    char* userInput = argv[1];

    if( access(userInput, F_OK ) == -1 ) {
        
        printf("\n Give a valid file name");
        printf("   gcc -o client client.c\n");
        printf("   ./client read.txt\n");
        return 0;
    }

     //client gets shared memory segment
     shared_memory_key = ftok(".", 'x');
     shared_memory_id = shmget(shared_memory_key, sizeof(struct memStruct), 0666);
     if (shared_memory_id < 0) {
          printf("*** shmget error (client) ***\n");
          exit(1);
     }

     printf("Client: Received a shared memory segment.\n");

     //client creates a pointer to the shared memory and attatches to it.
     shared_memory_ptr = (struct memStruct *) shmat(shared_memory_id, NULL, 0);
     if ((int) shared_memory_ptr == -1) {
          printf("*** shmat error (client) ***\n");
          exit(1);
     }
     printf("Client: Attached the shared memory.\n");

     //client does nothing until server changes status to indicate it is ready
     while (shared_memory_ptr->status != READY)
          sleep(1);


    //client opens text file to read to the shared memory segment.
    text_file = fopen (userInput, "r");
    
    //Think this could be used to prevent multiple clients from writing at the same time.
    shared_memory_ptr->status  = NOT_READY;

    //this one gets everything up to new line
    fscanf(text_file, "%[^\n]", &shared_memory_ptr->data);
    fclose(text_file);
    
     printf("Client: Wrote in shared memory: %s\n", &(shared_memory_ptr->data));
     
     //let the server know it has new info waiting
     shared_memory_ptr->status = CLIENT;
     printf("Client: Informed server data is waiting.\n");

     //this would need to happen to end process.
     shmdt((void *) shared_memory_ptr);
     printf("Client: Detached shared memory.\n");
     printf("Client: Done.\n");
     exit(0);

     return 0;
}