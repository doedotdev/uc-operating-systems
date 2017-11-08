#include <stdio.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/times.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <vector>
#include <sys/msg.h>
#include <string.h>

using namespace std;

int main(int argc, char** argv){
    
    char* email_input = argv[1];

    int create_pipe[2];
    FILE *execl_output;
    char buf[4096];
    int status;
    pipe(create_pipe);

    // Create a fork
    int fork_process = fork();
    if (fork_process == 0) {
        dup2(create_pipe[1], STDOUT_FILENO);
        close(create_pipe[0]);
        close(create_pipe[1]);
        execl("/bin/ps", "ps", "-e", "-o", "pid,comm", NULL);

	exit(-1);
    }

    fork_process = fork(); // actual fork()
    if (fork_process == 0) {
        dup2(create_pipe[1], STDOUT_FILENO);
        close(create_pipe[0]);
        close(create_pipe[1]);

        execl("/bin/ls", "ls", "-1", NULL);

	exit(-1);
    }

    close(create_pipe[1]);
    
    execl_output = fdopen(create_pipe[0], "r");
    
    vector<char*> vec;
    int fileCount = 0;
    int processCount = 0;
    bool flag = 0;
    
    while (fgets(buf, sizeof buf, execl_output) != NULL) {
        if (strcmp(to_string(strdup(buf)).substr(0,7), "PID COMM")) {  flag = 1; }
        if (flag == 0){
            fileCount++;
            } else {
            processCount++;
        }

        vec.push_back(strdup(buf)); // push buff onto vector
    }
    
    int fd = open("emailBody.txt", O_RDWR | O_CREAT | O_TRUNC, 0600);

    for (int i =0; i < fileCount+processCount; i++){
        int temp_size_vec = sizeof(vec[i]);
        write(fd, vec[i], temp_size_vec);
    }

    // output print statement
    string fileCountStr = to_string(fileCount);
    string processCountStr = to_string(processCount-1);
    string subject = "Files: " + to_string(fileCount) + " and Processes: " + processCountStr;

    execl("/bin/mail", "mail", "-s", subject, email_input < "emailBody.txt", NULL);

    wait(&status);
    
    return 0;
}
