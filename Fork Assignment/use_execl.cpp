// a tiny "shell"
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctype.h>
using namespace std;
int main () {

	cout << "\n\n\ndemonstrate the execl command" << endl;
	cout << "choose one:\n (A) show process\n(B) list directory" << endl;
	char choice[128];
	cin.getline(choice,128);
	choice[0] = tolower(choice[0]);
	
	char cmd[256];
	switch (choice[0]) {
		case 'a': cout << execl("/bin/ps", "ps", "-aux", 0); 
		case 'b': cout << execl("/bin/ls", "ls", "-l", 0);
		default: cout << execl("/net/d2/u6/f/ngo/326/a.out", "a.out", 0); 
	};

	cout << "this line should not be reached" << endl;
	exit(0);
}
