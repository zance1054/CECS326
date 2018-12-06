//binary fork

#include <unistd.h>
#include <stdlib>
#include <iostream>
using namespace std;

int main() {
	
	int k;
	long childPID;

	for(k=0; k<3; k++) {
		cout << "k: " << k << ", AND "
			<< getpid() << " is spawning a new child" << endl;
		childPID=fork();
		int testVar = k;
	}

	cout << "k = " << k << ", parent PID=" << getppid()
		<< ", childPID=" << childPID 
		<< ": PID " << getpid() << " now exits" << endl;

	exit(0);
}
