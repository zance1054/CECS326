// parent process and child processes

#include <unistd.h>
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {

	long childPID;
	int PCvar = 10;
	cout << "1\n2\n3\n";

	childPID = fork();
	if(childPID > 0) {
		int Pvar = 20;
		PCvar = 30;
		cout << "Parent process: pid " << getpid()
			<< ", ppid " << getppid()
			<< ", child " << childPID << endl;
	} else if (childPID == 0) {
		int Cvar = 400;
		PCvar = 500;
		cout << "Child process: pid " << getpid()
			<< ", ppid " << getppid()
			<< ", child " << childPID << endl;
	} else
		cout << "Spawn error - no child process" << endl;

	cout << "4\n5\n6\n";
	exit(0);
}		
