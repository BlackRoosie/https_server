#pragma once

#include "TcpListener.h"
#include "WebServerConfig.h"

class WebServer: public TcpListener
{
public:
	//WebServer(const char* ipAddress, int port):
	//	TcpListener(ipAddress, port){}
    WebServer(WebServerConfig &config):
        TcpListener(config){}

protected:

    virtual void onClientConnnected(int clientSocket);

    virtual void onClientDisconnected(int clientSocket);

    virtual void onMessageReceived(int clientSocket, const char* msg, int length);
};

