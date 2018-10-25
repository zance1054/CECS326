//Andre Barajas
//CS 326
//IPC Message Queue
//Fall 2018

//Loading Needed Libraries
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>
#include <bits/stdc++.h> 

using namespace std;

int rand();

int main()
{
	
    srand (time(NULL));

	
	// Data members
	string messageContent;
	int currentnumber = 0;
	int randomNum = 0;
	bool receiver1_alive = true;
	bool receiver2_alive = true;

    // Retreiving extant queue=different program
    int qid = msgget(ftok(".",'u'), 0);
	
    // structure to hold message in buffer
	struct buf 
	{
		long mtype; 
		char message[50]; // message information
	};//Ending buffer structure
	buf msg;
	int size = sizeof(msg)-sizeof(long);

	cout << "\t\t*********Hello World, This Is Sender 997***********"<<endl;

	do
	{
		
		do
		{
			randomNum = rand() % INT_MAX;
			currentnumber = randomNum;
		}while (randomNum % 997 != 0);

		messageContent = "997: " + to_string(currentnumber);
		
		// Sending to Receivers  in Queue
		if (receiver2_alive)
		{
			cout << "Sending to Receiver 2: " << messageContent;
			strcpy(msg.message, messageContent.c_str());
			msg.mtype = 118;
			cout << msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			cout << endl;
		}
		if (receiver1_alive)
		{
			cout << "Sending Message to Receiver 1: " << messageContent;
			strcpy(msg.message, messageContent.c_str());
			msg.mtype = 117;
			cout << msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			cout << endl;
			
		}

		// Receiving from Receivers in Queue
		if (receiver1_alive)
		{
			cout << "\n\t\t***********Standing By For Receiver 1 to receive . . . " << endl;
			msgrcv(qid, (struct msgbuf *)&msg, size, 1, 0);
			messageContent = msg.message;
			if (messageContent.compare("Receiver 1 Has Left") == 0)
			{
				receiver1_alive = false;
				cout << msg.message << endl <<endl;
			}
			else
			{
				cout << "Message Recieved." << endl << endl;
			}//Ending nested if else statement
		}
		if (receiver2_alive)
		{
			cout << "\nWaiting For Receiver 2 to receive . . . " << endl;
			msgrcv(qid, (struct msgbuf *)&msg, size, 2, 0);
			messageContent = msg.message;
			if (messageContent.compare("Receiver 2 Quitted") == 0)
			{
				receiver2_alive = false;
				cout << msg.message << endl <<endl;
			}
			else
			{
				cout << "Message Recieved." << endl << endl;
			}//Ending nested if else statement
		}//Ending if else statment
	} while(currentnumber > 100);
    return 0;
}//ending main method
