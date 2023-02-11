#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

void writeOuput (char *command, char *output);

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Error: Input one argument that is the input file name.");
        return 1;
    }
    int fd, shmfd;
    char *shmptr;
    FILE *fp;

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("File Read Error.");
        exit(1);
    }   

    shmfd = shm_open("sh_mem", O_RDWR | O_CREAT, 0666);
    ftruncate(shmfd, 4096);

    char **lines;
    fp = fopen(argv[1], "r");

    lines = (char**)malloc(4096 * sizeof(char*));
    for (int i = 0; i < 4096; i++) {
        lines[i] = (char*)malloc(4096 * sizeof(char));
    }

    int i = 0;

    while (fgets(lines[i], 4096, fp) != NULL && i < 4096) {
        i++;
    }

    fclose(fp);

    i = 0;

    while(lines[i][0]) { 
        char command[4096];
        strcpy(command, lines[i]);
        int pid = fork();
        if (pid == -1) {
            perror("Child process failure.");
            exit(1);
        }
        if (pid == 0) {
            char *cmd = strtok(command, " ");
            char *argv[5];
            argv[0] = cmd;
            int i = 1;
            while (1) {
                char *arg = strtok(NULL, " ");
                if (!arg) break;
                argv[i++] = arg;
            }
            argv[i] = NULL;

            for (int i = 0; i < 5 && argv[i]; i++) {
                int len;
                len = strlen(argv[i]);
                if (argv[i][len - 1] == '\n') {
                    argv[i][len - 1] = '\0';
                }
            }

            int fd = shm_open("sh_mem", O_CREAT | O_RDWR, 0666);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            if (execvp(argv[0], argv) == -1) {
                perror("Child command execution error");
                exit(1);
            }
            
        }
        if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            char buf[4096];
            shmptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
            sprintf(buf, "%s", shmptr);
            printf("buffer: %s \n", buf);
            writeOuput(command, buf);
            memset(shmptr, 0, 4096);
            munmap(shmptr, 4096);
        }
        i++;
    }
    close(shmfd);
    fclose(fp);
    return 0;
}

void writeOuput (char *command, char *output) { 
    FILE *fp;
    fp = fopen("output.txt", "a");
    fprintf(fp, "The output of : %s : is\n", command);
    fprintf(fp, "›››››››>>>>>>>> In%s‹‹‹«‹‹‹‹‹‹‹‹‹‹‹\n", output); 
    fclose(fp);
}