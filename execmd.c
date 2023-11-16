#include "shell.h"

void cmdexe(char **argv){
    char *cmd = NULL, *real_command = NULL;

    if (argv){
        /* get the command */
        cmd = argv[0];

        /* generate the path to this command before passing it to execve */
        real_command = get_location(cmd);

        /* execute the actual command with execve */
        execve(real_command, argv, NULL);
        exit(EXIT_FAILURE);
    }
    
}
