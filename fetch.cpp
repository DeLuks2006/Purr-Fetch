#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/utsname.h>
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

string getHostname()
{
	char hostname[50];
	int status = gethostname(hostname, sizeof(hostname));
	if (status == 0)
	{
		return hostname;
	}
	return "";
}

string getKernel()
{
	struct utsname osInfo{};
	uname(&osInfo);
	return static_cast<string>(osInfo.sysname) + " " + static_cast<string>(osInfo.release);
}
