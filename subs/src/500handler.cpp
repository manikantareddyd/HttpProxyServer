void sendHeader(char *statusCode, char *connection )
{
	std::string header = 
		"HTTP/1.0 "+(std::string)statusCode+"\r\n";
	header = header +
		"Connection: "+(std::string)connection+"\r\n"+
		"\r\n";
	send(clientSockId,(char *)header.c_str(),header.length(),0);
    if(DEBUG) printf("%s",(char *)header.c_str());
}

void handle500(std::string connection)
{
    if(DEBUG) printf("Handling 501\n");
	sendHeader((char *)"500 Internal Server Error",(char *)connection.c_str());
	
}

