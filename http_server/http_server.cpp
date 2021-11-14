#include "WebServer.h"
#include "WebServerConfig.h"
#include "WebServerConfigReader.h"

void main()
{
	WebServerConfigReader reader;
	WebServerConfig config = reader.read("config.txt");
	WebServer webServer(config);
	if (webServer.init() != 0)
		return;

	webServer.run();

	system("pause");
}






//#include <iostream>
//#include <fstream>
//#include <algorithm>
//#include <vector>
//#include <string>
//#include <unordered_map>
////#include <json/json.h>
////#include <exception>
////#include "nlohmann/json.hpp"
////#include <boost/property_tree/ptree.hpp>                                        
////#include <boost/property_tree/json_parser.hpp> 
//
//
//using namespace std;
////using json = nlohmann::json;
////namespace pt = boost::property_tree;
//
//int main()
//{
//	string path;
//	cin >> path;
//	ifstream input;
//	input.open(path);
//
//	string address, rootFolder, htmlFile;
//	int port, defaultCodeError;
//	unordered_map<string, string> data;
//
//	if (input.is_open())
//	{
//		string line, value, key;
//		int delimiter;
//		while (getline(input, line))
//		{
//			delimiter = line.find('=');
//			key = line.substr(0, delimiter);
//			value = line.substr(delimiter + 1);
//			data[key] = value;
//		}
//
//		address = data["address"];
//		port = stoi(data["port"]);
//		cout << address << '\t' << port << endl;
//	}
//	input.close();
//
//
//	//NOT WORKING FOR JSON FILE
//	// 
//	//Json::Reader reader;
//	//Json::Value root;
//	//reader.parse(input, root);
//
//	//cout << root["port"].asInt();
//
//	//pt::ptree root;
//	//pt::read_json("config.json", root);
//	//int port = root.get<int>("port");
//	//string address = root.get<string>("address");
//
//	//cout << port << '\t' << address << endl;
//
//
//
//	return 0;
//}