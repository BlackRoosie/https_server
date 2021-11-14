#pragma once

#include<WS2tcpip.h>
#include "WebServerConfig.h"

#pragma comment (lib, "ws2_32.lib")

class TcpListener
{
    //const char* m_ipAddress;
    //int m_port;
    int m_socket;
    fd_set m_master;

protected:
    WebServerConfig m_config;

    virtual void onClientConnnected(int clientSocket);

    virtual void onClientDisconnected(int clientSocket);

    virtual void onMessageReceived(int clientSocket, const char* msg, int length);

    void sendToClient(int clientSocket, const char* msg, int length);

    void broadcastToClients(int sendingClient, const char* msg, int length);

public:
    //TcpListener(const char* ipAddress, int port) :
    //    m_ipAddress(ipAddress), m_port(port) { }
    TcpListener(WebServerConfig config):
        m_config(config) { }

    int init();

    int run();

};
