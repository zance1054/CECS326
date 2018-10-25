//Andre Barajas
//CS 326
//IPC Message Queue 
//Fall 2018

//loading needed libaries
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
   
    bool menu = true;

	
    string realMessage, identifier, messageFromQueue;

    // Accessing queue in existince
	int qid = msgget(ftok(".",'u'), 0);
	cout << "\t\t********Queue Located, standing by**********\n" <<endl;

    //buffer used for message communcation
	struct buf 
	{
		long mtype; 
		char message[50]; // message information
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);

    while(menu)
    {
        msgrcv(qid, (struct msgbuf *)&msg, size, 117, 0);
        messageFromQueue = msg.message;
        identifier = messageFromQueue.substr(0,3);
        realMessage = messageFromQueue.substr(5);

        if(realMessage.compare("Exit") == 0)
        {
            // Sending Quit to 997
            strcpy(msg.message, "Receiver 1 Has Left");
            msg.mtype = 1;
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);

            // Sending Quit to Queue Center
            strcpy(msg.message, "Receiver 1 Removed");
            msg.mtype = 326;
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);

            cout << "\nTerminating Program....."<<endl;
            menu = false;
        }
        else
        {
            if (identifier.compare("997") == 0)
            {
                cout << identifier <<"'s Message Received: "<< realMessage <<endl;
                strcpy(msg.message, "Roger Roger from Receiver 1");
                msg.mtype = 1;
			    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
            }
            else
            {
                cout << identifier <<"'s Message Received: "<< realMessage <<endl;
            }//Ending nested if else statement
        }//Ending if else statemnet
    }//Ending while loop containing menu
    return 0;
}//Ending Main 

