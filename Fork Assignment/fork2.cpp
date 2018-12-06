// each child process has a different parent process

#include <cstdlib>
#include <unistd.h>
#include <iostream>
using namespace std;

int main() {
	
	int k;
	long childPID;

	for(k=0; k<3; k++) {
		cout << getpid() << " is spawning a new child" << endl;
		if(childPID = fork()) break;
		int testVar = k;
	}

	cout << "k = " << k << ", parent PID=" << getppid()
		<< ", childPID=" << childPID 
		<< ": PID " << getpid() << " now exits " << endl;

	exit(0);
}
