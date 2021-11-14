#include <iostream>
#include "WebServerConfig.h"

using namespace std;

string WebServerConfig::getAddress() { return address; }
int WebServerConfig::getPort() { return port; }
int WebServerConfig::getDefaultErrorCode() { return defaultErrorCode; }
string WebServerConfig::getRootFolder() { return rootFolder; }
string WebServerConfig::getHtmlFile() { return htmlFile; }

void WebServerConfig::setAddress(string a) { address = a;  }
void WebServerConfig::setPort(int p) { port = p; }
void WebServerConfig::setDefaultErrorCode(int error) { defaultErrorCode = error; }
void WebServerConfig::setRootFolder(string folder) { rootFolder = folder; }
void WebServerConfig::setHtmlFile(string file) { htmlFile = file; }
