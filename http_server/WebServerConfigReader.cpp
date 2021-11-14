#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "WebServerConfigReader.h"
//#include "json/json.h"
//#include <json/value.h>

using namespace std;

WebServerConfig WebServerConfigReader::read(string path)
{
	WebServerConfig data;
	ifstream input;
	input.open(path);

	unordered_map<string, string> settings;

	if (input.is_open())
	{
		string line, value, key;
		int delimiter;
		while (getline(input, line))
		{
			delimiter = line.find('=');
			key = line.substr(0, delimiter);
			value = line.substr(delimiter + 1);
			settings[key] = value;
		}

		data.setAddress(settings["address"]);
		data.setPort(stoi(settings["port"]));
		data.setDefaultErrorCode(stoi(settings["defaultErrorCode"]));
		data.setRootFolder(settings["rootFolder"]);
		data.setHtmlFile(settings["htmlFile"]);

	}
	input.close();

	return data;
}
