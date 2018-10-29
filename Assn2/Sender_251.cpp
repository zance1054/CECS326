//Andre Barajas
//CS 326 
//Fall 2018
//IPC message queue program Sender_251 class to send messages to receiver programs via message queue buffers
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
#include "get_info.h"

using namespace std;

int rand();
void get_info(int, struct msgbuf *, int, long);

int main()
{
	

	string decision;
	 srand (time(NULL));
	bool keepGoing = true;
    	// Buffer structure to hold message information to be used in active message queues
	struct buf 
	{
		long mtype; 
		char message[50]; // message information
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);

    // Retreiving extant queue 
    int qid = msgget(ftok(".",'u'), 0);
	
	// Provided Patch Code from prof Ngo fror Ubunto64-18.o used to terminate Receiver 1 when kill command is used
	strcpy(msg.message, "251: quit");
	msg.mtype = 117;
	get_info(qid, (struct msgbuf *)&msg, size, 117);

	cout << "\t\t*********Hello World, This Is Sender 251***********"<<endl;
	while(keepGoing)
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
			cout<< left << tempNumber << " : Recycle Bin"<<endl;
		}//Ending nested if else statement
	} //Ending While statement
    return 0;
}//Ending main method
