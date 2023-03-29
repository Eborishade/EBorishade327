#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	if (argc != 3) {
        fprintf(stderr, "%s requires two arguments. [prog_name] [env_var]\n", argv[0]);
		fprintf(stderr, "Usage: %s [program name] [env_var]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

    char *env_vars[6];
    env_vars[0] = "HOME="+getenv("HOME"); // ->uses printenv to get: "HOME=/home/..."
    env_vars[1] = "PATH=/usr/bin" ;
    env_vars[2] = "SHELL="+getenv("SHELL"); 
    env_vars[3] = "EXECD_PGM_NAME="+argv[2];
    env_vars[4] = "PWD="+getenv("PWD"); 
    //env_vars[5] = NULL;

    char* pgm_path = argv[1];
    char* new_pr_name = argv[2];

    prctl(pgm_path, new_pr_name);
    if(execle(pgm_path, new_pr_name, (char*)0, env_vars) == -1){
        FATAL("execle failed\n");
	}

	exit(EXIT_SUCCESS);

}