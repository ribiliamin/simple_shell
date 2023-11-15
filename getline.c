#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t nread;
    char *token;
    char *args[100];
    int i;
    pid_t pid;
    int status;

    while (1) {
        printf("$ ");
        nread = getline(&buffer, &bufsize, stdin);
        if (nread == -1) {
            break;
        }
        token = strtok(buffer, " \n");
        i = 0;
        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " \n");
            i++;
        }
        args[i] = NULL;
        pid = fork();
        if (pid == 0) {
            execve(args[0], args, NULL);
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
        } else {
            do {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    free(buffer);

    return 0;
}

