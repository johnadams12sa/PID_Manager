#include <iostream>
#include "pid_manager.cpp"

int main(){
	//initialize pid map from MIN_PID to MAX_PID
	allocate_map();
	
	// temporary variable pidPlaceHolder to hold value for pid
	int pidPlaceHolder = 0;

	//allocate all pid numbers for "tasks" to use
	for(int pidPlaceHolder = MIN_PID; pidPlaceHolder < MAX_PID; pidPlaceHolder++){
	pidPlaceHolder = allocate_pid();
	std:: cout << "New PID Assigned: " << pidPlaceHolder << std::endl;
	}

	//release task 2000
	release_pid(2000);
	
	//newly allocated task should get the pid number 2000 since it is the only available pid now
	pidPlaceHolder = allocate_pid();
	std:: cout << "New PID Assigned " << pidPlaceHolder << std::endl;
	
	//release a batch of pid numbers from 300 for when the "tasks" finish
	for(int i = MIN_PID; i < 3000; i++){
	release_pid(i);
	}

	//new task should get pid number 300 since it is the first available number from the beginning of map
	pidPlaceHolder = allocate_pid();
	std::cout << "New PID Assigned " << pidPlaceHolder << std::endl;
	return 0;
}
