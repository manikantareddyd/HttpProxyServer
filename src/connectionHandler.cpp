
void handleConnection()
{
	if(DEBUG)
        printf("Handling Connection Request\n\n");

	// while(1)
	// {
		memset(messageBuffer,0,BUFFERSIZE);
        bytesRead = 0;
		int tmp = 0;
		while(1)
		{
			tmp = recv(
				clientSockId,
				messageBuffer+bytesRead,
				BUFFERSIZE,
				0
        	);
			bytesRead = bytesRead + tmp;
			if(!strcmp(messageBuffer+bytesRead-4,"\r\n\r\n"))
				break;
		}

		if(bytesRead <= 0)
		{
			if(DEBUG) printf("Client has closed connection\r\n");
			return;
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
			if(DEBUG) printf("parse failed\n");
			handle500("C1lose");	// badRequestHandler();
			return ;
		}
		else
		{
			// printf("Method:%s\n", request->method);
			// printf("Host:%s\n", request->host);
			handleGetRequest(request);
		}
	// }
	return;
}
