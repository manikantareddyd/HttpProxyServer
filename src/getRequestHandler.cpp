void getResponseFromHost(std::string host, std::string request,int port)
{
    //Get respnse from HOST and send to CLient
    int	hostSockId;
	struct	sockaddr_in server;
	struct  hostent *hp;

	hostSockId = socket (AF_INET,SOCK_STREAM,0);

	server.sin_family = AF_INET;
	hp = gethostbyname((char *)host.c_str());
	bcopy ( hp->h_addr, &(server.sin_addr.s_addr), hp->h_length);
	server.sin_port = htons(port);
    
    int c = connect(
        hostSockId,
        (struct sockaddr *)&server,
        sizeof(server)
    );

    if(c<0)
    {
        if(DEBUG) printf("Server couldn't connect to Host: %s\n",(char *)host.c_str());
    }
    else
    {
        //Send reuqtes to HOST    
        send(hostSockId,(char *)request.c_str(),request.length(),0);
        while(1)
        {
        
            memset(messageBuffer,0,4096);
            //Recv form HOST
            bytesRead = recv(
                hostSockId,
                messageBuffer,
                4096,
                0
            );

            if(bytesRead<=0)
                break;
       
            //Send to CLient
            send( 
                clientSockId,
                messageBuffer,
                bytesRead,
                0
            );

        }
    }
    return ;
}

void handleGetRequest(ParsedRequest *request)
{
    //Request To Host
    std::string requestToHost = "";
    ParsedHeader_remove(request,"Host");
    ParsedHeader_remove(request,"Connection");
    requestToHost = requestToHost + "GET "+request->path+" HTTP/1.0\r\n";
    requestToHost = requestToHost + "Host: "+request->host+"\r\n";
    requestToHost = requestToHost + "Connection: Close\r\n";
    
    char buf[4096];
    memset(buf,0,4096);
    ParsedRequest_unparse_headers(request,buf,4096);
    
    requestToHost = requestToHost + buf;
    
    if(DEBUG) 
    {
        printf("\nRequest To Host\n\n");
        std::cout<<requestToHost<<std::endl;
    }
    int port;
    if(request->port != NULL) 
        port = atol(request->host);
    else 
        port = 80;
    
    getResponseFromHost(request->host,requestToHost,port); 
}

