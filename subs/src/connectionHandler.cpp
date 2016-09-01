
void handleConnection()
{
	if(DEBUG)
        printf("Handling Connection Request\n\n");


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
		//Consecutive /r/n to handle split requests
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
	//Parse the request
	ParsedRequest *request = ParsedRequest_create();
	if (ParsedRequest_parse(request, messageBuffer, len) < 0) 
	{
		if(DEBUG) 
			printf("parse failed\n");
		//Since an error has occured handle it aas 500
		handle500("Close");
		return ;
	}
	else
	{
		//Good going. There is still hope
		handleGetRequest(request);
	}

	return;
}
