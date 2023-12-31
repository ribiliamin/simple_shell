#include "shell.h"

int main(int ac, char **argv)
{
    /*char *prompt = "(Eshell) $ ";*/
    char *lineptr = NULL, *lineptr_cc = NULL;
    size_t n = 0;
    ssize_t char_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;
    pid_t child_pid;

    /* declaring void variables */
    (void)ac;

    /* Create a loop for the shell's prompt */
    while (1)
    {
        prompt();
        char_read = getline(&lineptr, &n, stdin);
        /* check if the getline function failed or reached EOF or user use CTRL + D */
        if (char_read == -1)
        {
            screenprint("Exiting shell....\n");
            return (-1);
        }

        /* allocate space for a copy of the lineptr */
        lineptr_cc = malloc(sizeof(char) * char_read);
        if (lineptr_cc == NULL)
        {
            perror("tsh: memory allocation error");
            return (-1);
        }
        /* copy lineptr to lineptr_cc */
        strcpy(lineptr_cc, lineptr);

        /********** split the string (lineptr) into an array of words ********/
        /* calculate the total number of tokens */
        token = strtok(lineptr, delim);

        while (token != NULL)
        {
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * num_tokens);

        /* Store each token in the argv array */
        token = strtok(lineptr_cc, delim);

        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        child_pid = fork();

        if (child_pid == -1) {
            screenprint("Error forking process.\n");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {

            /*Child proces*/ 
            /* execute the command */
            cmdexe(argv);
        } else {

		/*Parent process*/
		waitpid(child_pid, NULL, 0);
        }
    }

    /* free up allocated memory */
    free(lineptr_cc);
    free(lineptr);

    return (0);
}
