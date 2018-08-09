#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>


using namespace std;

class TCPClient

{
  public:
    TCPClient(string ip, unsigned short port);
    bool Connect();
    bool write(char* data, unsigned short length);
    bool read(char* data, unsigned short& size, unsigned short maxSize);
    ~TCPClient();
 private:
    string m_ip ;
    unsigned short m_port ;
    int sock, n;
    struct sockaddr_in addr;
};

#endif
