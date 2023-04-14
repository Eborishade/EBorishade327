#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define UNUSED (void)

/*
Program Description:

Wait to recieve SIGINT from Terminal. [env kill --signal -SIGINT -q <proc A pid> <proc B pid>] 
If SIGINT recieved, catch, send SIGUSR1 to process A (A pid found in siginfo)
Process A will send SIGUSR1 as ACK.
Catch ACK.

*/


sig_atomic_t send_signal_flag = 0; //atomics cannot be interrupted
sig_atomic_t send_to_pid = 0; 
sig_atomic_t ack_recieved_flag = 0;

void signal_handler(int signum, siginfo_t *siginfo, void *context){
    
    //If recieving Kill (SIGINT)
    if (signum == SIGINT){
        send_signal_flag = 1;  //set flag to send SIGUSR1 to a process
        send_to_pid = siginfo->si_value.sival_int; //get dest pid
    }
    //If recieving ACK (SIGUSR0)
    else if (signum == SIGUSR1){
        ack_recieved_flag = 1; //set flag that ACK recieved

    }
}

void send_signal_to_pid(pid_t dest_pid){
    //use sigqueue to send the SIGUSR1 signal along with the dest_pid

    printf("process_b sending signal to pid");
    union sigval my_pid;
    my_pid.sival_int = getpid();
    if (sigqueue(dest_pid, SIGUSR1, my_pid) < 0 ){
        perror("process_b.send_signal_to_pid");
    }
}

void do_work(){
    pause();

    //If Kill Signal recieved (SIGINT)
    if (send_signal_flag){
        printf("\nSignal recieved. The send_to_pid is %d\n", send_to_pid);
        send_signal_flag = 0;

        //send SIGUSR
        send_signal_to_pid(send_to_pid);
    }

    //If ACK recieved (SIGUSR1)
    if (ack_recieved_flag) { 
        printf("\nACK recieved! (from: %d)\n", send_to_pid);
        ack_recieved_flag = 0;
    }

}

int main(int argc, char* argv[0]){
    UNUSED argc;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    
    act.sa_sigaction = signal_handler;

        /*
        Note the __sigaction_handler is an unnamed union. That
        is why we can't assign the handler this way:

        act.__sigaction_handler.sa_sigaction = signal_handler;

        The sigaction structure provides defines for sa_sigaction
        and sa_handler.
    */
    act.sa_flags = SA_SIGINFO;
    if (sigaction(SIGINT, &act, 0) < 0){ 
        perror("process b");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGUSR1, &act, 0) < 0){ 
        perror("process b");
        exit(EXIT_FAILURE);
    }

    printf("\n%s pid is %d.\n", argv[0], getpid());
    while (1){
        do_work();
    }
}