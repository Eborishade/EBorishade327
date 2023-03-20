#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    printf("Current Host Name:           %s\n", hostname);
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
            printf("CPU Type:                  %s\n", vendorID);
        } else if (strncmp(data, "model name", 10) == 0){ //line 5 in file
            memset(modelName, '\0', sizeof(modelName));
            sscanf(data, "%*s %*s : %80c", modelName);
            printf("CPU Model:                  %s", modelName);
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
    fscanf(fptr, "%63c", version);
    fclose(fptr);
    printf("Kernel Version:           %s\n", version);
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
            printf("Memory Configured:            %s", memTotal);
        } else if (strncmp(data, "MemFree", 7) == 0){ //line 5 in file
            memset(memFree, '\0', sizeof(memFree));
            sscanf(data, "%*s %80c", memFree);
            printf("Memory Available:              %s", memFree);
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


    printf("Uptime:               \t\t%i:%i:%i:%i\n", hour, min, sec, msec);
}

//PRINT EXECUTION MODE STATISTICS
void print_exe_stats() {
    FILE* fptr = fopen("/proc/sys/kernel/hostname", "r");
    if (fptr == NULL) {
        perror("print_hostname");
        exit(1);
    }
    char hostname[64];
    fscanf(fptr, "%s", hostname);
    fclose(fptr);
    printf("Current Host Name:           %s\n", hostname);
}

int main (void) {
    printf("------------------------------------------------------\n");
    printf("                 System Info\n");
    printf("------------------------------------------------------\n");
    print_hostname();
    print_cpu();
    print_version();
    print_memory();
    print_uptime();
    print_exe_stats();

}