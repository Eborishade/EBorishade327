#include <stdio.h>

int main(int argc, char *argv[]){

    printf("hello, world\n");
    printf("argc=%d argv[0]=%s]\n", argc, argv[0] );

    if (argc >=2) {
        printf("argv[1]=%s\n", argv[1]);
    }

    printf("argv[9]=%s\n", argv[9]);
}