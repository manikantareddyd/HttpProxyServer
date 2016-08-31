
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
		
	createSocket();
	bindSocket();
	listenThroughSocket();
	
	while(1)
	{
		acceptNewConnection();
	}
	
	return 0;

}
