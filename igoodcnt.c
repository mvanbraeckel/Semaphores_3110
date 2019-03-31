/**
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 31/03/2019
 * CIS*3110: Operating Systems A4 - Synchronizing Threads with POSIX Semaphores
 * --> Uses semaphores to synchronously increment a global variable being
 * 		accessed by the same two threads
 */

// ============================== INCLUDES ==============================
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// ========================== GLOBAL VARIABLES ==========================
int NITER = 1000000;
int cnt = 0;
sem_t mutex;

// ======================== FUNCTION PROTOTYPES =========================
void* Count();
void* thread();

/**
 * Accepts a single cmd line integer argument for NITER value
 */
int main(int argc, char * argv[]) {
	// declare variables
	pthread_t tid1, tid2;

	sem_init(&mutex, 0, 1); // initialize the semaphor

	// validate arguments
	// implementation


	// Parsing the arguments passed to your C program
	// Including the number of times that each thread increments
	// the shared count cnt
	// For example, NITER = 20000;


	// Display the number of times (entered by the user) that each thread
	// increments the shared count cnt
// PLEASE DO NOT remove or modify the following code 
	printf("2*NITER is [%d]\n", 2*NITER);
// End of code section 

	// create both threads
	if(pthread_create(&tid1, NULL, thread, NULL)) {
		printf("\n ERROR creating thread 1");
		exit(EXIT_FAILURE);
	}
	if(pthread_create(&tid2, NULL, thread, NULL)) {
		printf("\n ERROR creating thread 2");
		exit(EXIT_FAILURE);
	}

	// wait for each thread to finish
	if(pthread_join(tid1, NULL)) {
		printf("\n ERROR joining thread");
		exit(EXIT_FAILURE);
	}
	if(pthread_join(tid2, NULL)) {
		printf("\n ERROR joining thread");
		exit(EXIT_FAILURE);
	}

    // Display the value of count cnt
// PLEASE DO NOT remove or modify the following code
	printf("\nCounter is [%d]\n", cnt);
	if(cnt == 2 * NITER) {
		printf("\nPASS\n");
	} else {
		printf("\nFAIL\n");
	}
// End of code section

	sem_destroy(&mutex); // destroy the semaphor
	pthread_exit(NULL);
	return 0;
} // end main

// ======================================================================

/**
 * Increments the global count NITER times
 */
void* Count() {
    int i, tmp;
    for(i = 0; i < NITER; i++) {
        tmp = cnt;      // copy the global cnt locally
        tmp = tmp+1;    // increment the local copy
        cnt = tmp;      // store the local value into the global cnt 
    }
	return NULL;
}

/**
 * Uses semaphores to increment the global count NITER times while blocking other thread
 */
void* thread() {
	sem_wait(&mutex);	// wait on the semaphore
	Count();			// inrement count in the critical section
	sem_post(&mutex);	// increment value of the semaphore (signal)
	return NULL;
}
