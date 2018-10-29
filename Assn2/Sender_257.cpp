//Andre Barajas
//CS 326
//Fall 2018
//IPC Message Queue Program Sender 257 to send messages to Receiver programs via message buffers

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

int rand();

int main()
{

    // Retreiving extant queue 
    int qid = msgget(ftok(".",'u'), 0);
	string decision;
	int value;
    srand (time(NULL));
    // Structure buffer to hold mesage informtion 
	struct buf
	{
		long mtype; 
		char message[50]; // Message information no more than fifty chars long 
		bool receiverRunning; //receiver check 
	};//Ending buffer structure

	buf msg;
	int size = sizeof(msg)-sizeof(long);

	msg.receiverRunning = true;

	cout << "\t\t***********Hello World, This Is Sender 257**************"<<endl;

	while(msg.receiverRunning)
	{
		value = rand();
		if(value % 257 == 0)
		{
			cout << "Sended : "<< value <<endl;
			string m = "257: " + to_string(value);
			strcpy(msg.message, m.c_str());
			msg.mtype = 118;
			msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			msgrcv(qid, (struct msgbuf *)&msg, size, 120, 0);
		}//Ending if condition
	}//Ending while statement
	cout << "\n\t\t***********Terminating Receiver 2**************"<<endl;
    return 0;
}//Ending main method for sender 257 
