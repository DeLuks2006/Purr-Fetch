#include <iostream>
#include <string>
#include <fstream>

double getUptime();
// Returns uptime in seconds
std::string getShell();
std::string getDistro();
std::string getHostname();
std::string getKernel();
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
