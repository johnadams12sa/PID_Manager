//pid_manager.cpp
#include "pid_manager.h"
#include <exception>
#include <iostream>

//initialize all values in the map to 0 to signify unused pid, return 1 upon success, otherwise -1
int allocate_map(){
	//unsure how to specify the exception when the program can't execute the function
	//***UPDATE*** it works when the PID number went out of bounds, so it will return -1 because it wont allocate it
	if (nullptr) return -1;
for (int i = MIN_PID; i < MAX_PID; i++) {
		pid_map[i] = 0;
	}
	return 1;
}

//search through pid_map for unused pid, if found, change value to 1 and return pid, otherwise return -1
int allocate_pid(){
	for( int i = MIN_PID; i < MAX_PID; i++) {
		//if pid_map is 0, it is unused, therefore we can allocate this pid
if (pid_map[i] == 0) {
			pid_map[i] = 1;
			return i;
		}
	}
	//if no pids are available, return -1 to signify no available pids to allocate
	return -1;
}

//take the pid and reset the value from 1 to 0 so that the pid can be used again
void release_pid(int pid) {
	pid_map[pid] = 0;
	std::cout << "released pid " << pid << std::endl;
}

