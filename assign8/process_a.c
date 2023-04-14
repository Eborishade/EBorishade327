#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#define UNUSED (void)


/* Program Description: 

Wait to recieve SIGUSR1 to process B
If SIGUSR1 Recieved, send SIGUSR1 & PID back as ACK. - get process B pid from siginfo

*/


sig_atomic_t process_b_pid = 0;
sig_atomic_t send_signal_flag = 0;

void signal_handler (int signum, siginfo_t* siginfo, void* context){
    if (signum == SIGUSR1){
        //SIGNAL RECIEVED
        send_signal_flag = 1;  //set flag to send SIGUSR1 to process B
        process_b_pid = siginfo->si_value.sival_int; //get dest pid of B
    }
}

void send_ACK_to_pid(pid_t dest_pid){
    //use sigqueue to send the SIGUSR1 signal along with the dest_pid

    printf("process_a sending ACK signal to pid\n");
    union sigval my_pid;
    my_pid.sival_int = getpid();
    if (sigqueue(dest_pid, SIGUSR1, my_pid) < 0 ){
        perror("process_a.send_ACK_to_pid");
    }
}

int main(int argc, char* argv[0]){
    UNUSED argc;
    printf("\n%s pid is %d.\n", argv[0], getpid());

    //register signal handler
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    
    act.sa_sigaction = signal_handler;


    act.sa_flags = SA_SIGINFO;
    if (sigaction(SIGINT, &act, 0) < 0){ 
        perror("process a");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGUSR1, &act, 0) < 0){ 
        perror("process a");
        exit(EXIT_FAILURE);
    }

    while(1){
        pause();
        ///check if sig recieved process b pid should be > 0
        if (process_b_pid > 0){
            printf("%s signal recieved from process b pid %d\n", argv[0], process_b_pid);
        }

        if (send_signal_flag){
            send_ACK_to_pid(process_b_pid);
        }
             
    }
}