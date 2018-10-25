//Andre Barajas
//CS 326
//IPC Message Queue
//Fall 2018

//Loading needed libraries

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
    
	
	// Variables
	string decision;
  	string messageFromQueue;
	string realMessage;
	string identifier;
	bool menu = true;

	// buffer with the message information
	struct buf
	{
		long mtype; 
		char message[50]; // message data
		bool receiverRunning; 
	};

	buf msg;
	int size = sizeof(msg)-sizeof(long);
	int msgRcvdCount=0;
	msg.receiverRunning = true;

	// retrieving extant queue 
	int qid = msgget(ftok(".",'u'), 0);
	cout << "Queue Located, Standing By.....\n" <<endl;
   		 while(menu)
  		  {
				msgrcv(qid, (struct msgbuf *)&msg, size, 118, 0);
				messageFromQueue = msg.message;
				identifier = messageFromQueue.substr(0,3);
				realMessage = messageFromQueue.substr(5);

				//max messages this program may receive is set to 5000 to quit just in case
				if(msgRcvdCount==5000)
				{
					// Sending quit to 257
					msg.receiverRunning = false;
					msg.mtype = 120;
					msgsnd(qid, (struct msgbuf *)&msg, size, 0);

					// Sending Quit to 997
				   	 strcpy(msg.message, "Receiver 2 Exiting");
				   	 msg.mtype = 2;
				   	 msgsnd(qid, (struct msgbuf *)&msg, size, 0);

					// Sending quit to Queue Center
					msg.mtype = 326;
					strcpy(msg.message, "Receiver 2  Has Now Exited ");
					msgsnd(qid, (struct msgbuf *)&msg, size, 0);
				    cout << "\nTerminating Program....."<<endl;
				    menu = false;
				}
				else if(identifier.compare("997") == 0)
				{
					msgRcvdCount++;
					cout << identifier <<"'s Message Received: "<< realMessage <<endl;
				  	strcpy(msg.message, "Roger Roger from Receiver 2");
				 	 msg.mtype = 2;
					 msgsnd(qid, (struct msgbuf *)&msg, size, 0);
				}
				else
				{
					msgRcvdCount++;
				  	cout << identifier << "'s Message Received: "<<realMessage<<endl;
					msg.mtype = 120;
					msgsnd(qid, (struct msgbuf *)&msg, size, 0);
				}//Ending nested if else statment
   		 }//Ending while loop statement
    return 0;
}//Ending main method
