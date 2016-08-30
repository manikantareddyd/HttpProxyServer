void sendHeader(char *statusCode, char *contentType, char *contentLength, char *connection )
{
	std::string header = 
		"\r\nHTTP/1.1 "+(std::string)statusCode+"\r\n"+
		"Date:"+getNowTime()+"\r\n"+
		"Server:"+"Thor/1.4.5"+"\r\n"+
		"Content-Length:"+(std::string)contentLength+"\r\n";
	if((std::string)contentType == "unknown")
		header = header + "Media-Type: Application/octet-stream\r\n";
	else
		header = header + "Content-Type:"+(std::string)contentType+"\r\n";
	header = header +
		"Connection:"+(std::string)connection+"\r\n"+
		"\r\n";
	send(clientSockId,(char *)header.c_str(),header.length(),0);
    printf("%s",(char *)header.c_str());
}

void handle501(std::string connection)
{
    if(DEBUG) printf("Handling 501\n");
	std::string message = "<center>ERROR 501. Requested Method is not Implemented.\r\n</center>\r\n";
	char numBuf[5];
	memset(numBuf,0,5);
	sprintf(numBuf,"%ld",message.length());
	sendHeader((char *)"501 Not Implemented",(char *)"text/html",numBuf,(char *)connection.c_str());
	memset(messageBuffer,0,BUFFERSIZE);
	sprintf(messageBuffer,"%s\r\n",(char *)message.c_str());
	send(clientSockId,messageBuffer,message.length(),0);
    printf("%s",messageBuffer);
}

