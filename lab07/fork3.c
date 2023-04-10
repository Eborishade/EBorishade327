#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
Zombie State Case
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


            if(execlp("ps","ps", "-l", "--forest", NULL) == -1)
                perror("Child exec of 'ps'");
            
            exit(EXIT_FAILURE);
            break; //note: without break, child also runs default case

        default:
            //ret val from fork in parent
            printf("Parent! PID# %d\n", getpid());
            printf("Waiting for Child process (PID# %d)...\n\n", ret);
            
            sleep(10);//child lives & dies before parent - becomes zombie
            system("ps -l --forest");
            system("cat");
            

            /*Zombie created due to comments:
            pid_t child_pid = wait(0); //without wait, parent does not know child is already dead; does not clean up (ZOMBIE PROCESS born)
            printf("Child process died! (PID %d)\n", child_pid);
           */
            break;

    }
    
	
    printf("PID %d: Hello, fork.\n\n", getpid()); //both parent and child return (ret twice)
	exit(EXIT_SUCCESS);
}

