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

