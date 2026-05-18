#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>


/*
1. To compile:

gcc -o t0 t0.c -lpthread -Wall

2. To run

./t0
*/

void *mythread(void *arg) {
    printf("%s\n", (char *) arg);
    return NULL;
}

int main(int argc, char *argv[]) {                    
    if (argc != 1) {
	fprintf(stderr, "usage: main\n");
	exit(1);
    }

    pthread_t p1, p2, p3, p4, p5;
    printf("main: begin\n");
    // create two threads
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");
    pthread_create(&p3, NULL, mythread, "C");
    pthread_create(&p4, NULL, mythread, "D");
    pthread_create(&p5, NULL, mythread, "E");
    // join waits for the threads to finish
    // pthread_join(p1, NULL);
    // pthread_join(p2, NULL);
    // pthread_join(p3, NULL);
    // pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    // sleep(3);
    printf("main: end\n");
    return 0;
}

