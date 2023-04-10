#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
Basic Fork Usage
*/
int main()
{
    pid_t ret;
    switch((ret = fork())){
        case -1:
        perror("fork failed!");
        break;
        
        case 0:
            //Return val from fork in child
            printf("CHILD! PID# %d\n", getpid());
            break; //note: without break, child also runs default case


        default:
            //ret val from fork in parent
            printf("Parent! PID# %d\n", getpid());
            printf("Child process = PID# %d\n", ret);
            printf("Waiting for Child process (PID# %d)...\n\n", ret);
            
            pid_t child_pid = wait(0); //without wait, parent dies before child (now orphaned)
            printf("Child process(PID %d) died!\n", child_pid);
            break;

    }
    
    /*SAME AS: 
	if (fork() == -1)
		FATAL("fork failed!\n");
    //Return val from fork in the parent is child PID
    //Return val from fork in child is 0
    */
	
    printf("PID %d: Hello, fork.\n\n", getpid()); //both parent and child return (ret twice)
	exit(EXIT_SUCCESS);
}

