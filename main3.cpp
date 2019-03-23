#include "pid_manager.cpp"

int main(){
	//initialize pid map from MIN_PID to MAX_PID, initializes to value of 0 for each spot
	allocate_map();
	startProgram();

	return 0;
}