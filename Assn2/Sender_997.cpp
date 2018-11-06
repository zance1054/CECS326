//Andre Barajas
//Tiffany Paiva
//Alexander Fielding
//CS 326 
//Fall 2018
//IPC Message Queue Program Sender 997 used to send signals to receiver programs via message buffer
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>
#include <bits/stdc++.h> // Int_max

using namespace std;

int rand();

int main()
{
 
	string messageContent;
	int number = 0;
	int randomNum = 0;
	bool keepGoing = true;
	bool receiver1_alive = true;
	bool receiver2_alive = true;
   	 srand (time(NULL));
    // Retreiving The extant queue 4rm other apps
    int qid = msgget(ftok(".",'u'), 0);
	
    // Buffer structure to hold message information 
	struct buf 
	{
		long mtype; 
		char message[50]; // message information no more than fifty chars
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);

	cout << "\t\t***********Hello World, This is Sender 997************"<<endl;

	do{
		
		do{
			randomNum = rand() % INT_MAX;
			number = randomNum;
		}while (randomNum % 997 != 0);

		messageContent = "997: " + to_string(number);
		
		// Sending to Receivers
		if (receiver1_alive)
		{
			cout << "\t\t*************Sending to Receiver 1: " << messageContent;
			strcpy(msg.message, messageContent.c_str());
			msg.mtype = 117;
			cout << msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			cout << endl;
		}
		if (receiver2_alive)
		{
			cout << "\t\t**************Sending to Receiver 2: " << messageContent;
			strcpy(msg.message, messageContent.c_str());
			msg.mtype = 118;
			cout << msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			cout << endl;
		}

		// Receiving from Receivers
		if (receiver1_alive)
		{
			cout << "\n\t\t*************Standing By For Receiver 1 to get Message . . . " << endl;
			msgrcv(qid, (struct msgbuf *)&msg, size, 1, 0);
			messageContent = msg.message;
			if (messageContent.compare("\t\t*************Receiver 1 Left************") == 0)
			{
				receiver1_alive = false;
				cout << msg.message << endl <<endl;
			}
			else
			{
				cout << "\t\t************Successfully Recieved Message*************" << endl << endl;
			}
		}
		if (receiver2_alive)
		{
			cout << "\n\t\t***********Standing By For Receiver 2 to get Message*********" << endl;
			msgrcv(qid, (struct msgbuf *)&msg, size, 2, 0);
			messageContent = msg.message;
			if (messageContent.compare("\t\t***********Receiver 2 Left") == 0)
			{
				receiver2_alive = false;
				cout << msg.message << endl <<endl;
			}
			else
			{
				cout << "\t\t************Successfully Recieved Message*********" << endl << endl;
			}//Ending nested if else statement
		}//Ending nested if else statement
	} while(number > 100);//Ending do while statement
    return 0;
}//Ending main method for Sende 997
