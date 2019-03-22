//pid_manager.h
//constants for the minimum and maximum values for PID for any processes, and declare the array of pid values
const int MIN_PID = 300;
const int MAX_PID = 5000;
const int numberOfThreads = 100;
int pid_map[4700];

//functions the pid_manager can use to manage pids
int allocate_map();
int allocate_pid();
void release_pid(int pid);
