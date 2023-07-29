#include <iostream>
#include <string>
#include <fstream>
using std::string;

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
	if (std::ifstream("/proc/uptime") >> uptimeSeconds)
	{
		return uptimeSeconds;
	}
	return -1;
}

