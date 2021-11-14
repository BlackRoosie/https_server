#pragma once

#include <iostream>
#include "WebServerConfig.h"

class WebServerConfigReader {
public:
	WebServerConfig read(string path);
	WebServerConfigReader() { };
};