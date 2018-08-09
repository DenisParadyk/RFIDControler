#include "TCPClient.h"

TCPClient::TCPClient(string ip, unsigned short port){
    m_ip = ip;
    m_port = port;

}

bool TCPClient::Connect(){

    struct sockaddr_in server;

    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
       return false;
    }

    server.sin_addr.s_addr = inet_addr(m_ip.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(m_port);

    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        return false;
    }

    return true;
}

bool TCPClient::write(char* data, unsigned short size){

    n = send(sock, data, size, 0);
    if (n < 0){

        return false;
    }
    return true;
}

bool TCPClient::read(char* data, unsigned short& size, unsigned short maxSize){

     n = recv(sock, data, maxSize,  MSG_PEEK);
     if (n < 0){

         return false;
    }
    return true;
}

TCPClient::~TCPClient(){

    close(sock);
}
