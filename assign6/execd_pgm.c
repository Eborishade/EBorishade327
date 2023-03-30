#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/prctl.h>

int main (void) {
    char *name = getenv("EXECD_PGM_NAME");
    if (name == NULL) {
        perror("Error: EXECD_PGM_NAME environment variable not set\n");
        exit(EXIT_FAILURE);
    }

    //execute change name
    if (prctl(PR_SET_NAME, name) == -1) {
        perror("Error setting process name\n");
        exit(EXIT_FAILURE);
    }

    if (system("printenv") == -1) {
        perror("Error executing printenv\n");
        exit(EXIT_FAILURE);
    }
    
    if (system("ps") == -1) {
        perror("Error executing ps\n");
        exit(EXIT_FAILURE);
    }


    return EXIT_SUCCESS;
}