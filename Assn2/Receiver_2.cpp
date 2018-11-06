//Andre Barajas
//Tiffany Paiva
//Alexander Fielding
//CS 326 
//Fall 2018
//IPC Message Queue to send message to handle receiver and sender signals 
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
    


	
	string decision;
  string messageFromQueue;
	string realMessage;
	string identifier;
		bool keepGoing = true;
	//Buffer structure to hold message information to be used in active queues 
	struct buf
	{
		long mtype; 
		char message[50]; //Message information 
		bool receiverRunning; //Receiver check
	};

	buf msg;	
	int size = sizeof(msg)-sizeof(long);
	int msgRcvdCount=0;
	msg.receiverRunning = true;

	// Retreiving the extant queue from other programs
	int qid = msgget(ftok(".",'u'), 0);
	cout << "\t\t*********Located Queue , now waiting************\n" <<endl;
    while(keepGoing)
    {
        msgrcv(qid, (struct msgbuf *)&msg, size, 118, 0);
        messageFromQueue = msg.message;
	identifier = messageFromQueue.substr(0,3);
        realMessage = messageFromQueue.substr(5);

				//no more than 5000 or exit will occur
				if(msgRcvdCount == 5000)
				{
						// signal send to quit: 257
						msg.receiverRunning = false;
						msg.mtype = 120;
						msgsnd(qid, (struct msgbuf *)&msg, size, 0);

						// Sending Quit to 997
					    strcpy(msg.message, "Receiver 2 Quitted");
					    msg.mtype = 2;
					    msgsnd(qid, (struct msgbuf *)&msg, size, 0);

						// Sending quit to Queue Center
						msg.mtype = 326;
						strcpy(msg.message, "\t\t**********Exit Successful: Receiver 2************");
						msgsnd(qid, (struct msgbuf *)&msg, size, 0);
					    cout << "\n\t\t***********Terminating Program***************"<<endl;
					    keepGoing = false;
     			        }
				else if(identifier.compare("997") == 0)
				{
					msgRcvdCount++;
					cout << identifier <<"'s Message Received: "<< realMessage <<endl;
				        strcpy(msg.message, "confirmed: Receiver 2");
				        msg.mtype = 2;
			                msgsnd(qid, (struct msgbuf *)&msg, size, 0);
				}
				else
				{
								msgRcvdCount++;
				 	 cout << identifier << "'s Message Received: "<<realMessage<<endl;
								msg.mtype = 120;
								msgsnd(qid, (struct msgbuf *)&msg, size, 0);
				}//Ending if else statement
    }//Ending While statement
    return 0;
}//Ending main method for receiver two 
