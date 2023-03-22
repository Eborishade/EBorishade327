#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//PRINT HOSTNAME
void print_hostname() {
    FILE* fptr = fopen("/proc/sys/kernel/hostname", "r");
    if (fptr == NULL) {
        perror("print_hostname");
        exit(1);
    }
    char hostname[64];
    fscanf(fptr, "%63s", hostname);
    fclose(fptr);
    printf("Current Host Name:          \t   %s\n", hostname);
}

//PRINT CPU INFO
void print_cpu() {
    FILE* fptr = fopen("/proc/cpuinfo", "r");
    if (fptr == NULL) {
        perror("print_cpu");
        exit(1);
    }

    char line[1024], vendorID[256], modelName[256];
    char *data = fgets(line, sizeof(line), fptr);
    while (data != NULL){
        if (strncmp(data, "vendor_id", 9) == 0){ //line 2 in file
            memset(vendorID, '\0', sizeof(vendorID));
            sscanf(data, "%*s %*s %s", vendorID);
            printf("CPU Type:                \t   %s\n", vendorID);
        } else if (strncmp(data, "model name", 10) == 0){ //line 5 in file
            memset(modelName, '\0', sizeof(modelName));
            sscanf(data, "%*s %*s : %50c", modelName);
            printf("CPU Model:                  \t   %s", modelName);
            break;
        }
        data = fgets(line, sizeof(line), fptr);
    }
    fclose(fptr);
}

//PRINT KERNEL VERSION
void print_version() {
    FILE* fptr = fopen("/proc/version", "r");
    if (fptr == NULL) {
        perror("print_version");
        exit(1);
    }
    char version[64];
    fscanf(fptr, "%32c", version);
    fclose(fptr);
    printf("Kernel Version:           \t   %s\n", version);
}

//PRINT MEMORY INFO
void print_memory() {
    FILE* fptr = fopen("/proc/meminfo", "r");
    if (fptr == NULL) {
        perror("print_memory");
        exit(1);
    }
    char line[1024], memTotal[32], memFree[32];;
    char *data = fgets(line, sizeof(line), fptr);
    while (data != NULL){
        if (strncmp(data, "MemTotal", 8) == 0){ //line 2 in file
            memset(memTotal, '\0', sizeof(memTotal));
            sscanf(data, "%*s %32c", memTotal);
            printf("Memory Configured:                 %s", memTotal);
        } else if (strncmp(data, "MemFree", 7) == 0){ //line 5 in file
            memset(memFree, '\0', sizeof(memFree));
            sscanf(data, "%*s %80c", memFree);
            printf("Memory Available:                  %s", memFree);
            break;
        }
        data = fgets(line, sizeof(line), fptr);
    }
    fclose(fptr);
}

//PRINT UPTIME STATISTICS
void print_uptime() {
    FILE* fptr = fopen("/proc/uptime", "r");
    if (fptr == NULL) {
        perror("print_hostname");
        exit(1);
    }
    char data[32];
    fscanf(fptr, "%s", data);
    fclose(fptr);
    double uptime = strtod(data, NULL);//uptime in seconds

    //time math
    int hour, min, sec, msec;
    min = uptime/60;
    hour = (uptime/60)/60; //or divided by 3600. 3600 sec in hour.
    sec = uptime;
    msec = uptime*1000;
    //reduce
    msec = msec-(1000*sec);
    sec = sec-(60*min);
    min = min-(60*hour);


    printf("Uptime:              \t\t   %i:%i:%i:%i\n", hour, min, sec, msec);
}

//PRINT EXECUTION MODE STATISTICS
void print_exe_stats() {
    FILE* fptr = fopen("/proc/stat", "r");
    if (fptr == NULL) {
        perror("print_stats");
        exit(1);
    }
    
    // /proc/stats returns amount of time, measured in units of USER_HZ
    /// We just need first line: 10 values 1 label - 11 elements

    char line[64];
    fscanf(fptr, "%63c", line);
    fclose(fptr);

	char *data = strtok(line, " "); //Begin splitting string. This line gets first element out of the way, 10 elements remaining.
    int stats[10]; 

    //split rest of string into stats
	for(int i = 0; i<10; i++)
	{
        data = strtok(NULL, " ");
		if(data){
            stats[i] = strtod(data, NULL);
        }
	}
   //stats[1] = user     stats[3] = system     stats[4] = idle
    int t_userm = stats[0];
    int t_sysm = stats[2];
    int t_idlem = stats[3];

    //current units of USER_HZ = (1/100ths of a second [or 'centiseconds'] on most architectures)
    //confirm system timing using:  long clock_ticks = sysconf(_SC_CLK_TCK); 52630centiseconds -> 526300ms (52630*10)

    // num / (clock_ticks/1000) = num(milliseconds)

    long clock_ticks = sysconf(_SC_CLK_TCK);
    t_userm = t_userm / (clock_ticks/1000.0);
    t_sysm = t_sysm / (clock_ticks/1000.0);
    t_idlem = t_idlem / (clock_ticks/1000.0);

    printf("Time Spent in User Mode:           %i ms\n", t_userm);
    printf("Time Spent in System Mode:         %i ms\n", t_sysm);
    printf("Time Spent in Idle Mode:           %i ms\n", t_idlem);

}


int main (void) {
    printf("----------------------------------------------------------------------------\n");
    printf("                \t\tSystem Information\n");
    printf("----------------------------------------------------------------------------\n");
    print_hostname();
    print_cpu();
    print_version();
    print_memory();
    print_uptime();
    print_exe_stats();

}