//Andre Barajas
//Tiffany Paiva
//Alexander Fielding
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
    
    

    	string messageFromQueue, identifier, realMessage;
	bool keepGoing = true;
   	 // Grabbing the existing queue from the other program
	int qid = msgget(ftok(".",'u'), 0);
	cout << "\t\t********Located Queue, Standing by**********\n" <<endl;

   	 //Buffer structure to hold message information to be used in active queues
	struct buf 
	{
		long mtype; 
		char message[50]; // message info no more than fifty chars long 
	};//Ending Structure 
	buf msg;
	int size = sizeof(msg)-sizeof(long);

    while(keepGoing)
    {
        msgrcv(qid, (struct msgbuf *)&msg, size, 117, 0);
        messageFromQueue = msg.message;
        identifier = messageFromQueue.substr(0,3);
        realMessage = messageFromQueue.substr(5);

        if(realMessage.compare("quit") == 0)
        {
            // Signal sent to Quit, 997.
            strcpy(msg.message, "\t\t***********Leaving: Receiver 1*************");
            msg.mtype = 1;
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);

            // Sending Quit to Queue Center
            strcpy(msg.message, "\t\t************Exit successful: Receiver 1");
            msg.mtype = 326;
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);

            cout << "\n\t\t***********Terminating Program************"<<endl;
            keepGoing = false;
        }
        else
        {
            if (identifier.compare("997") == 0)
            {
                cout << identifier <<"'s Message Received: "<< realMessage <<endl;
                strcpy(msg.message, "success from Receiver 1");
                msg.mtype = 1;
			    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
            }
            else
            {
                cout << identifier <<"'s Message Received: "<< realMessage <<endl;
            }//ending nested if else statement
        }//Ending if else statement
    }//ending while statement
    return 0;
}//Ending main method for receiver one 
