#pragma once
#include <iostream>
#include <string.h>
#include <sstream>
#include <WS2tcpip.h>
#include <vector>
#include "TcpListener.h"
#include "Rsa.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

void TcpListener::onClientConnnected(int clientSocket)
{
    //string welcomeMsg = "Welcome";
    //sendToClient(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1);
}

void TcpListener::onClientDisconnected(int clientSocket)
{

}

void TcpListener::onMessageReceived(int clientSocket, const char* msg, int length)
{
    // broadcastToClients(clientSocket, msg, length);
}

void TcpListener::sendToClient(int clientSocket, const char* msg, int length)
{
    send(clientSocket, msg, length, 0);
}

void TcpListener::broadcastToClients(int sendingClient, const char* msg, int length)
{
    for (int i = 0; i < m_master.fd_count; i++)
    {
        SOCKET outSock = m_master.fd_array[i];
        if (outSock != m_socket && outSock != sendingClient)
        {
            sendToClient(outSock, msg, length);
        }
    }
}

int TcpListener::init()
{
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        return wsOk;
    }

    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == INVALID_SOCKET)
    {
        return WSAGetLastError();
    }

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(m_config.getPort());
    inet_pton(AF_INET, m_config.getAddress().c_str(), &sa.sin_addr);

    if (bind(m_socket, (sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
    {
        return WSAGetLastError();
    }

    if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        return WSAGetLastError();
    }

    FD_ZERO(&m_master);

    FD_SET(m_socket, &m_master);

    return 0;

}

int TcpListener::run()
{
    bool running = true;

    while (running)
    {
        fd_set copy = m_master;

        int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

        for (int i = 0; i < socketCount; i++)
        {
            SOCKET sock = copy.fd_array[i];

            if (sock == m_socket)
            {
                SOCKET client = accept(m_socket, nullptr, nullptr);

                FD_SET(client, &m_master);

                onClientConnnected(client);
            }
            else // It's an inbound message
            {
                const int buf_size = 4096;
                char buf[buf_size];
                //vector<char> data;
                ZeroMemory(buf, buf_size);

                int bytesIn = recv(sock, buf, buf_size, 0);

                if (bytesIn <= 0)
                {
                    onClientDisconnected(sock);
                    closesocket(sock);
                    FD_CLR(sock, &m_master);
                }
                else
                {
                    //while (bytesIn > 0)
                    //{
                    //    for(int j = 0; j < buf_size; j++)
                    //    data.push_back(buf[j]);
                    //}
                    //onMessageReceived(sock, &data, data.size());
                    onMessageReceived(sock, buf, buf_size);
                }
            }
        }
    }

    FD_CLR(m_socket, &m_master);
    closesocket(m_socket);

    while (m_master.fd_count > 0)
    {
        SOCKET sock = m_master.fd_array[0];

        FD_CLR(sock, &m_master);
        closesocket(sock);
    }

    WSACleanup();
    return 0;
}
