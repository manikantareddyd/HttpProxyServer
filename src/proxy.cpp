
#include "proxy.h"

void sgHandler(int sig)
{
	noOfChildren-- ;
}

int main(int argc, char *argv[])
{
	signal(SIGCHILD,sgHandler);
	if(argv[1]!=NULL)
		PORT = atoi(argv[1]);
	if(argv[2]!=NULL) 
		rootDir = argv[2];
	createSocket();
	bindSocket();
	listenThroughSocket();
	
	while(1)
	{
		if(noOfChildren < 20) 
		{
			noOfChildren++;
			acceptNewConnection();
		}
	}
	return 0;
}
