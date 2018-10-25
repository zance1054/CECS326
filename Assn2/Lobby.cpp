//Andre Barajas
//CS 326
//IPC Message Queue 
//Fall 2018

//Downloading needed libraries
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
    // ftok() will generate a queue for the process
	int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);
    	cout << "Created cQueue ....\n" <<endl;

    
    string messageFromQueue, identifier, realMessage;
   
    // buffer with the message contents
	struct buf
	{
		long mtype; 
		char message[50]; // Message information
	};

	buf data;	//creating instance of buffer
	int size = sizeof(msg)-sizeof(long);

    // standing by for receivers to end before clearing queue
    msgrcv(qid, (struct msgbuf *)&msg, size, 326, 0);

    cout << data.message << endl;

    msgrcv(qid, (struct msgbuf *)&msg, size, 326, 0);
    
    cout << data.message << "\n"<< endl;

    cout << "Receivers Are All dequed, Deleting Queue now...." << endl;

    //Deleting message queue
    msgctl (qid, IPC_RMID, NULL);


    return 0;
}//Ending Main method
