void getResponseFromHost(std::string host, std::string request)
{
    int	sd;
	struct	sockaddr_in server;
	struct  hostent *hp;

	sd = socket (AF_INET,SOCK_STREAM,0);

	server.sin_family = AF_INET;
	hp = gethostbyname((char *)host.c_str());
	bcopy ( hp->h_addr, &(server.sin_addr.s_addr), hp->h_length);
	server.sin_port = htons(80);
    // std::cout<<hp->h_name<<hp->h_addr<<std::endl;
    int c = connect(
        sd,
        (struct sockaddr *)&server,
        sizeof(server)
    );
    if(c<0)
    {
        printf("It failed\n");
    }
    else
    {
        printf("YOLO\n");
        send(sd,(char *)request.c_str(),request.length(),0);
        while(1)
        {
            printf("YOLO\n");
        
            memset(messageBuffer,0,4096);
            bytesRead = recv(
                sd,
                messageBuffer,
                4096,
                0
            );
            if(bytesRead<=0)
                break;
            
            
            int bytesToWrite = 4096;
            int bytesWritten = 0;
            int bytesOverHead = 0;
            /*
                We need to loop till all writable bytes are written to socket buffer.
                If write fails in between we loop back and write the remaining bytes
            */
            send( 
                    clientSockId,
                    messageBuffer + bytesOverHead,
                    bytesRead,
                    0
                );
            // while(1)
            // {
            //     bytesWritten = send( 
            //         clientSockId,
            //         messageBuffer + bytesOverHead,
            //         bytesToWrite,
            //         0
            //     );
                
            //     if(bytesWritten == bytesToWrite) 
            //         break;
            //     else
            //     {
            //         bytesOverHead = bytesOverHead + bytesWritten;
            //         bytesToWrite = 4096 - bytesOverHead;
            //     }
            // }

        }
    }
    return ;
}

void handleGetRequest(ParsedRequest *request)
{
    std::string requestToHost = "";
    ParsedHeader_remove(request,"Host");
    ParsedHeader_remove(request,"Connection");
    requestToHost = requestToHost + "GET "+request->path+" HTTP/1.1\r\n";
    requestToHost = requestToHost + "Host: "+request->host+"\r\n";
    requestToHost = requestToHost + "Connection: Close \r\n";
    char buf[4096];
    memset(buf,0,4096);
    ParsedRequest_unparse_headers(request,buf,4096);
    requestToHost = requestToHost + buf;
    printf("\nRequest To Host\n\n");
    std::cout<<requestToHost<<std::endl;
    getResponseFromHost(request->host,requestToHost); 
}

