//Libraries
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ctime>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

//My files
#include "globalVariables.cpp"
#include "../utils/proxy_parse.c"
#include "500handler.cpp"
#include "getRequestHandler.cpp"
#include "connectionHandler.cpp"
#include "socketFunctions.cpp"

