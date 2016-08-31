
#include "proxy.h"

void sgHandler(int sig)
{
	noOfChildren-- ;
}

int main(int argc, char *argv[])
{

	signal(SIGCHLD,sgHandler);
	
	if(argv[1]!=NULL)
		PORT = atoi(argv[1]);
	//Create Socket	
	createSocket();
	//Bind Scoket
	bindSocket();
	//Listen through SOcket
	listenThroughSocket();
	
	while(1)
	{
		//Accept a new connection
		acceptNewConnection();
	}
	
	return 0;

}
