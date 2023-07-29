#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using std::string;
using std::ifstream;

double getUptime();
// Returns uptime in seconds
string getShell();
string getDistro();
string getHostname();
string getKernel();
void display();

int main()
{
	return 0;
}

double getUptime()
{
	double uptimeSeconds;
	if (ifstream("/proc/uptime") >> uptimeSeconds)
	{
		return uptimeSeconds;
	}
	return -1;
}

string getShell()
{
	string shell = getenv("SHELL");
	return shell;
}

string getDistro()
{
	ifstream inputStream;
	string text;
	string distro;
	string::size_type startPosition;
	string::size_type endPosition;

	inputStream.open("/etc/os-release");
	while (inputStream >> text)
	{
		if (text.find("PRETTY_NAME") != string::npos)
		{
			startPosition = text.find("\"") + 1;
			endPosition = text.find("\"", startPosition);
			distro = text.substr(startPosition, endPosition - startPosition);
			return distro;
		}
	}
	return "";
}

