#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	if (argc != 3) {
        fprintf(stderr, "%s requires two arguments. [prog_name] [env_var]\n", argv[0]);
		fprintf(stderr, "Usage: %s [program name] [env_var]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

  //create environmental variables to pass to execd program
  char *env_vars[6];

  /*Better way to define env_vars
    #define SHELL
    #define HOME
    #define PWD
    #define EXECD_PGM "EXECD_PGM"
    #define PATH_VALUE "usr/bin"
    ...
    env_vars[0] = make_env_var(HOME, getenv(HOME));
    env_vars[1] = make_env_var(PATH, getenv(PATH_VALUE));
    env_vars[2] = make_env_var(SHELL, getenv(SHELL));
    env_vars[3] = argv[2]
    env_vars[4] = make_env_var(PWD, getenv(PWD));
  */

  env_vars[0] = calloc(100, sizeof(char));
  strcpy(env_vars[0], "HOME=");
  strcat(env_vars[0], getenv("HOME")); 
  
  env_vars[1] = "PATH=/usr/bin";

  env_vars[2] = calloc(100, sizeof(char));
  strcpy(env_vars[2], "SHELL=");
  strcat(env_vars[2], getenv("SHELL"));
  
  env_vars[3] = argv[2];

  env_vars[4] = calloc(100, sizeof(char));
  strcpy(env_vars[4], "PWD=");
  strcat(env_vars[4], getenv("PWD"));
  env_vars[5] = NULL;
  

  //get path to program and new name to run under
  char* pgm_path = argv[1];
  char* pgm_name = argv[2];

  if(execle(pgm_path, pgm_name, NULL, env_vars) == -1){
    perror("execle Failed");
    //free space on failure then exit
    for (int i = 0; i < (sizeof(env_vars) / sizeof(env_vars[0])); i++){
      free(env_vars[x])
    }
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS); //unreachable
}