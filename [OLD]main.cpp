#include <iostream>
#include <mutex>
#include <pthread.h>
#include <stdlib.h>
#include <cstdlib>
#include <assert.h>
#include <unistd.h>
#include "pid_manager.cpp"

//initialize mutex to use for locking and unlocking mechanism.
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//function to allocate pid, sleep, and then release pid. Does not have parameters and returns nothing
void* doPIDStuff(void* args){
	//lock the critical section of allocating pids
	pthread_mutex_lock(&mutex);

	//assign the pid without other threads interfering
	int threadPID = allocate_pid();

	//unlock the critical section for other threads to use shared resource map
	pthread_mutex_unlock(&mutex);

	//sleep(1+(std::rand() % numberOfThreads));
	sleep(1 + (std::rand() % 3));
	release_pid(threadPID);
}

int main(){
	//initialize pid map from MIN_PID to MAX_PID, initializes to value of 0 for each spot
	allocate_map();
	
	//initialize an array of thread identifiers. Need to use pthread_t to create a reference for threads. Each thread needs one
	//to work properly
	pthread_t thread_ID[numberOfThreads];

	//initialize thread argument array and result_code, which will be used for assertions
	int thread_args[numberOfThreads];
	int result_code;

	//assign each thread the task of allocating a pid. Use pthread_create to create the threads
	for(int i = 0; i < numberOfThreads; i++){
		thread_args[i] = i;
		result_code = pthread_create(&(thread_ID[i]), NULL, doPIDStuff, NULL);
		assert(!result_code);
	}

	//join all the threads back together
	for(int j = 0; j < numberOfThreads; j++){
		result_code= pthread_join(thread_ID[j],NULL);
		assert(!result_code);
	}

	return 0;
}
