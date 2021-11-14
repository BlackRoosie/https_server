#pragma once

#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <streambuf>
#include "WebServer.h"

using namespace std;

void WebServer::onClientConnnected(int clientSocket)
{

}

void WebServer::onClientDisconnected(int clientSocket)
{

}

void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
    // Parse out the client's request string e.g. GET /index.html HTTP/1.1
    istringstream iss(msg);
    vector<string> parsed((istream_iterator<string>(iss)), istream_iterator<string>());

    // Some defaults for output to the client (404 file not found 'page')
    string content = "<h1>404 Not Found</h1>";
    string htmlFile = m_config.getHtmlFile();
    int errorCode = m_config.getDefaultErrorCode();

    if (parsed.size() >= 3 && parsed[0] == "GET")
    {
        htmlFile = parsed[1];

        // If the file is just a slash, use index.html. This should really
        // be if it _ends_ in a slash. I'll leave that for you :)
        if (htmlFile == "/")
        {
            htmlFile = m_config.getHtmlFile();
        }
    }

    ifstream f(m_config.getRootFolder() + htmlFile);

    if (f.good())
    {
        string str((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
        content = str;
        errorCode = 200;
    }

    f.close();

    ostringstream oss;
    oss << "HTTP/1.1 " << errorCode << " OK\r\n";
    oss << "Cache-Control: no-cache, private\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
    oss << "\r\n";
    oss << content;

    string output = oss.str();
    int size = output.size() + 1;

    sendToClient(clientSocket, output.c_str(), size);


}


