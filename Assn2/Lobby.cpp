//Andre Barajas
//CS 326
//Fall 2018
//IPC Message Queue program to communicate with receiver one and two via Senders 997, 257 etc. 


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

int main() 
{   
    // Employing ftok() method to generate a queue for receviers
    //and senders.
	int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);
    cout << "\t\t*********Initiating Queue Now************\n" <<endl;


    string messageFromQueue, identifier, realMessage;
   
    // buffer structure to hold message data
	struct buf
	{
		long mtype; 
		char message[50]; // message information
	};

	buf msg;	//initializes instance of buffer
	int size = sizeof(msg)-sizeof(long);

    // standing by for Current Receivers to finish and then clearing the existing queue
    msgrcv(qid, (struct msgbuf *)&msg, size, 326, 0);

    cout << msg.message << endl;

    msgrcv(qid, (struct msgbuf *)&msg, size, 326, 0);
    
    cout << msg.message << "\n"<< endl;

    cout << "\t\t********Receivers Leaving, Removing Queue************" << endl;

   //Removing message queue 
    msgctl (qid, IPC_RMID, NULL);


    return 0;
}//Ending Main method
