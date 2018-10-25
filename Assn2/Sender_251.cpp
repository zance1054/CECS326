//Andre Barajas
//CS 326
//IPC Message Queue
//Fall 2018

//Loading needed libaries
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "Get_Info.h"

using namespace std;

int rand();
void get_info(int, struct msgbuf *, int, long);

int main()
{
	
    srand (time(NULL));

	
	bool menu = true;

	
	string decision;

    // Structure to hold message information
	struct buf 
	{
		long mtype; 
		char message[50]; // Message infomation
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);

    // Retrieving extant queue from other program
    int qid = msgget(ftok(".",'u'), 0);
	
	// Patch Code provided by professor Ngo (i.e. patch64-18.o) to terminate Receiver 1 after kill command
	strcpy(msg.message, "251: quit");
	msg.mtype = 117;
	get_info(qid, (struct msgbuf *)&msg, size, 117);

	cout << "Hello World, This Is Sender 251"<<endl;
	while(menu)
	{
		
		int tempNumber = rand();
		if (tempNumber % 251 == 0)
		{
			cout.width(15);
			cout << left << tempNumber << " : Sended"<<endl;
			decision = "251: " + to_string(tempNumber);
			strcpy(msg.message, decision.c_str());
			msg.mtype = 117;
			msgsnd(qid, (struct msgbuf *)&msg, size, 0);	
		} 
		else
		{
			cout.width(15); 
			cout<< left << tempNumber << " : Trash"<<endl;
		}//Ending nested if else statement
	} //Ending while loop
    return 0;
}
