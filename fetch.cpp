#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/utsname.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::to_string;

struct Uptime {
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
string buildUptimeString(Uptime uptime);
void display();

int main() {
	display();
	return 0;
}

Uptime getUptime() {
	const int DAY_IN_SECONDS = 86400;
	const int HOUR_IN_SECONDS = 3600;
	const int MINUTE_IN_SECONDS = 60;

	long uptimeSeconds;
	Uptime uptime;

	if (ifstream("/proc/uptime") >> uptimeSeconds) {
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

string getShell() {
	string shell = getenv("SHELL");
	return shell;
}

string getDistro() {
	ifstream inputStream;
	string text;
	string distro;
	string::size_type startPosition;
	string::size_type endPosition;

	inputStream.open("/etc/os-release");
	while (inputStream >> text) {
		if (text.find("PRETTY_NAME") != string::npos) {
			startPosition = text.find("\"") + 1;
			endPosition = text.find("\"", startPosition);
			distro = text.substr(startPosition, endPosition - startPosition);
			return distro;
		}
	}
	return "";
}

string getHostname() {
	char hostname[50];
	int status = gethostname(hostname, sizeof(hostname));
	if (status == 0) {
		return hostname;
	}
	return "";
}

string getKernel() {
	struct utsname osInfo {};
	uname(&osInfo);
	return static_cast<string>(osInfo.sysname) + " " +
		   static_cast<string>(osInfo.release);
}

string buildUptimeString(Uptime uptime) {
	string uptimeString = "";
	if (uptime.days > 0) {
		uptimeString += to_string(uptime.days) + " days, ";
	}
	if (uptime.hours > 0) {
		uptimeString += to_string(uptime.hours) + "h ";
	}
	if (uptime.minutes > 0) {
		uptimeString += to_string(uptime.minutes) + "m ";
	}
	if (uptime.seconds > 0) {
		uptimeString += to_string(uptime.seconds) + "s";
	}
	return uptimeString;
}

void display() {
	Uptime uptime = getUptime();
	string uptimeString = buildUptimeString(uptime);
	string shell = getShell();
	string distro = getDistro();
	string hostname = getHostname();
	string kernel = getKernel();

	string white = "\033[0;0m";

	cout << endl;
	cout << "(\\_/)      \033[0;33m"
		 << "uptime:\t" << uptimeString << white << endl;
	cout << "(oᴥo)      \033[0;31m"
		 << "shell:\t" << shell << white << endl;
	cout << "|U°U|      \033[0;35m"
		 << "distro:\t" << distro << white << endl;
	cout << "|   |      \033[0;34m"
		 << "hostname:\t" << hostname << white << endl;
	cout << "'U_U'      \033[0;36m"
		 << "kernel:\t" << kernel << white << endl;
	cout << "  U";
	cout << endl;
}
