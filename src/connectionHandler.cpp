
void handleConnection()
{
	if(DEBUG)
        printf("Handling Connection Request\n\n");

	while(1)
	{
		memset(messageBuffer,0,BUFFERSIZE);
        bytesRead = recv(
            clientSockId,
            messageBuffer,
            BUFFERSIZE,
            0
        );

		if(bytesRead <= 0)
		{
			if(DEBUG) printf("Client has closed connection\r\n");
			break;
		}

		if(DEBUG)
		{
			printf("%s\n",messageBuffer);
			printf("bytesRead %d\n",bytesRead);
		}

		int len = strlen(messageBuffer);
		ParsedRequest *request = ParsedRequest_create();
		if (ParsedRequest_parse(request, messageBuffer, len) < 0) 
		{
			printf("parse failed\n");
			handle501("close");	// badRequestHandler();
			return ;
		}
		else
		{
			printf("Method:%s\n", request->method);
			printf("Host:%s\n", request->host);

		}
    }
	return;
}
