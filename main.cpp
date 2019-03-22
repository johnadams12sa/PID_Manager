#include <iostream>
#include <mutex>
#include <pthread.h>
#include <stdlib.h>
#include <cstdlib>
#include <assert.h>
#include <unistd.h>
#include "pid_manager.cpp"

//function to allocate pid, sleep, and then release pid
void* doPIDStuff(void* args){
	int threadPID = allocate_pid();
	sleep(1+(std::rand() % numberOfThreads));
	release_pid(threadPID);
}

int main(){
	//initialize pid map from MIN_PID to MAX_PID
	allocate_map();
	
	//initialize an array of thread identifiers. Need to use pthread_t to create a reference for threads. Each thread needs one
	pthread_t thread_ID[numberOfThreads];

	//initialize thread argument array
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