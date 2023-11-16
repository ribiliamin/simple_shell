#include "shell.h"

char *get_location(char *cmd1){
    char *path, *path_copy, *path_token, *file_path;
    int cmd_len, len_dir;
    struct stat buffer;
    
    path = getenv("PATH");

    if (path){
        /* Duplicate the path string -> remember to free up memory for this because strdup allocates memory that needs to be freed*/ 
        path_copy = strdup(path);
        /* Get length of the command that was passed */
        cmd_len = strlen(cmd1);


        /* Let's break down the path variable and get all the directories available*/
        path_token = strtok(path_copy, ":");

        while(path_token != NULL){
            /* Get the length of the directory*/
            len_dir = strlen(path_token);
            /* allocate memory for storing the command name together with the directory name */
            file_path = malloc(cmd_len + len_dir + 2); /* NB: we added 2 for the slash and null character we will introduce in the full command */
            /* to build the path for the command, let's copy the directory path and concatenate the command to it */
            strcpy(file_path, path_token);
            strcat(file_path, "/");
            strcat(file_path, cmd1);
            strcat(file_path, "\0");

            /* let's test if this file path actually exists and return it if it does, otherwise try the next directory */
            if (stat(file_path, &buffer) == 0){
                /* return value of 0 means success implying that the file_path is valid*/

                /* free up allocated memory before returning your file_path */
                free(path_copy);

                return (file_path);
            }
            else{
                /* free up the file_path memory so we can check for another path*/
                free(file_path);
                path_token = strtok(NULL, ":");

            }
        
        }

        /* if we don't get any file_path that exists for the command, we return NULL but we need to free up memory for path_copy */ 
        free(path_copy);

        /* before we exit without luck, let's see if the command itself is a file_path that exists */
        if (stat(cmd1, &buffer) == 0)
        {
            return (cmd1);
        }


        return (NULL);
    
    }


    return (NULL);
}
