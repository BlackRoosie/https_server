#pragma once
#include <iostream>

using namespace std;

class WebServerConfig {

	string address;
	int port;
	int defaultErrorCode;
	string rootFolder;
	string htmlFile;

public:

	string getAddress();
	int getPort();
	int getDefaultErrorCode();
	string getRootFolder();
	string getHtmlFile();

	void setAddress(string);
	void setPort(int);
	void setDefaultErrorCode(int);
	void setRootFolder(string);
	void setHtmlFile(string);
	
};