#include<stdio.h>
#include<stdlib.h>

void out(void){
    printf("atexit() success!\n");
}

int main(int argc, char** argv) {
    if (atexit(out)){
        fprintf(stderr,"atexit() fail!\n");
    }

    return 0;
}