
#include "proxy.h"

int main(int argc, char *argv[])
{
	if(argv[1]!=NULL)
		PORT = atoi(argv[1]);
	if(argv[2]!=NULL) 
		rootDir = argv[2];
	createSocket();
	bindSocket();
	listenThroughSocket();
	
	while(1)
	{
		acceptNewConnection();
	}
	return 0;
}
