#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/utsname.h>
using std::string;
using std::ifstream;

struct Uptime
{
	int days = 0;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
};

Uptime getUptime();
// Returns an Uptime object
string getShell();
string getDistro();
string getHostname();
string getKernel();
void display();

int main()
{
	return 0;
}

Uptime getUptime()
{
	const int DAY_IN_SECONDS = 86400;
	const int HOUR_IN_SECONDS = 3600;
	const int MINUTE_IN_SECONDS = 60;

	long uptimeSeconds;
	Uptime uptime;

	if (ifstream("/proc/uptime") >> uptimeSeconds)
	{
		uptime.days = uptimeSeconds / DAY_IN_SECONDS;
		uptimeSeconds = uptimeSeconds % DAY_IN_SECONDS;
		uptime.hours = uptimeSeconds / HOUR_IN_SECONDS;
		uptimeSeconds = uptimeSeconds % HOUR_IN_SECONDS;
		uptime.minutes = uptimeSeconds / MINUTE_IN_SECONDS;
		uptimeSeconds = uptimeSeconds % MINUTE_IN_SECONDS;
		uptime.seconds = uptimeSeconds;
	}
	return uptime;
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

