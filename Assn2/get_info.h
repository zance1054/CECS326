//Andre Barajas
//CS 326 
//Fall 2018
//IPC Message Queue

//Loading needed libraries
#include<iostream>
#include<signal.h>
#include<unistd.h>
#include <sys/types.h>

void get_info(int qid, msgbuf *exitmsg, int size, long mtype);
#include<iostream>
#include<signal.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring> // memcpy
#include <cstdlib> // malloc

using namespace std;
int gqid;
msgbuf *gmbuf;
int gsize;
long gmtype;

void sig_handler(int signo)
{
	if (signo == SIGUSR1) {
		gmbuf->mtype = gmtype;
		msgsnd(gqid,gmbuf, gsize, 0);
		free (gmbuf);
		_exit(0);
	}
}//Ending Sig_handler function
void get_info(int qid, msgbuf *exitmsg, int size, long mtype) {
	signal(SIGUSR1, sig_handler);
	gqid = qid;
	gsize = size;
	gmtype = mtype;
	gmbuf = (struct msgbuf *)malloc(size);
	memcpy (gmbuf,exitmsg,size);
}//Ending get Info function


