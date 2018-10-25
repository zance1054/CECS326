//Andre Barajas
//CS 326
//IPC Message Queue
//Fall 2018


//loading needed libraries
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

    srand (time(NULL));


	
	int key;

    // Retrieving extant queue other program
    int qid = msgget(ftok(".",'u'), 0);

    // declare my message buffer and its size
	struct buf
	{
		long mtype; // required
		char message[50]; // mesg content
		bool receiverRunning; //flag to check receiver status
	};

	buf msg;
	int size = sizeof(msg)-sizeof(long);

	msg.receiverRunning = true;

	cout << "Hello World: This Is Sender 257"<<endl;

	while(msg.receiverRunning)
	{
		key = rand();
		if(key % 257 == 0)
		{
			cout << "Sended : "<< key <<endl;
			string m = "257: " + to_string(key);
			strcpy(msg.message, m.c_str());
			msg.mtype = 118;
			msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			msgrcv(qid, (struct msgbuf *)&msg, size, 120, 0);
		}//Ending if condition statement
	}//Ending while loop statment
	cout << "\n\t\t*********Receiver 2 Has Left:/, Exiting**********"<<endl;
    return 0;
}//Ending main method
