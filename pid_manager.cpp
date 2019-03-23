//pid_manager.cpp
#include "pid_manager.h"
#include <exception>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <stdlib.h>
#include <cstdlib>
#include <assert.h>
#include <unistd.h>

//initialize mutex to use for locking and unlocking mechanism.
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//initialize all values in the map to 0 to signify unused pid, return 1 upon success, otherwise -1
int allocate_map()
{
	//unsure how to specify the exception when the program can't execute the function
	//***UPDATE*** it works when the PID number went out of bounds, so it will return -1 because it wont allocate it
	if (nullptr)
		return -1;
	for (int i = MIN_PID; i < MAX_PID; i++)
	{
		pid_map[i] = 0;
	}
	return 1;
}

//search through pid_map for unused pid, if found, change value to 1 and return pid, otherwise return -1
int allocate_pid()
{
	for (int i = MIN_PID; i < MAX_PID; i++)
	{
		//if pid_map is 0, it is unused, therefore we can allocate this pid
		if (pid_map[i] == 0)
		{
			pid_map[i] = 1;
			std::cout << "Allocated pid " << i << std::endl;
			return i;
		}
	}
	//if no pids are available, return -1 to signify no available pids to allocate
	return -1;
}

//take the pid and reset the value from 1 to 0 so that the pid can be used again
void release_pid(int pid)
{
	if (pid >= 300 && pid <= 5000)
	{
		pid_map[pid] = 0;
		std::cout << "released pid " << pid << std::endl;
	}
	else
	{
		std::cout << "WARNING: Invalid pid passed to function \n";
	}
}

//function to allocate pid, sleep, and then release pid. Does not have parameters and returns nothing
void *doPIDStuff(void *args)
{
	//lock the critical section of allocating pids
	pthread_mutex_lock(&mutex);
	//assign the pid without other threads interfering
	int threadPID = allocate_pid();
	//unlock the critical section for other threads to use shared resource map
	pthread_mutex_unlock(&mutex);

	sleep(1 + (std::rand() % numberOfThreads));

	//lock the critical section of allocating pids
	pthread_mutex_lock(&mutex);
	release_pid(threadPID);
	//unlock the critical section for other threads to use shared resource map
	pthread_mutex_unlock(&mutex);
}

void startProgram(){
	//initialize an array of thread identifiers. Need to use pthread_t to create a reference for threads. Each thread needs one
	//to work properly
	pthread_t thread_ID[numberOfThreads];

	//initialize thread argument array and result_code, which will be used for assertions
	int thread_args[numberOfThreads];
	int result_code;

	//assign each thread the task of allocating a pid. Use pthread_create to create the threads
	for (int i = 0; i < numberOfThreads; i++)
	{
		thread_args[i] = i;
		result_code = pthread_create(&(thread_ID[i]), NULL, doPIDStuff, NULL);
		assert(!result_code);
	}

	//join all the threads back together
	for (int j = 0; j < numberOfThreads; j++)
	{
		result_code = pthread_join(thread_ID[j], NULL);
		assert(!result_code);
	}
}