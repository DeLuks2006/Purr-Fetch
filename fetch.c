//bin/true && exec /usr/bin/env tcc -run "$0"
#include <errno.h>
#include <libgen.h>
#include <pwd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>

// hostname 4 - read file /etc/hostname
// kernel 5 - read file or osInfo.sysname
// ascii art 0

void display(void);
/*const*/ long uptime(char **buf);
const char *shell(char **buf);
const char *distro(char **buf);
const char *hostname(char **buf);
const char *kernel(char **buf);

int main(void) {
	display();
	return 0;
}
const char *shell(char **buf) {
	const char *shell;
	uid_t uid;
	struct passwd *passwd_of_user;
	// This will break if the Environment is ever changed
	shell = getenv("SHELL");
	if (shell != NULL) {
		return shell;
	}
	uid = getuid();
	errno = 0;
	passwd_of_user = getpwuid(uid);
	if (passwd_of_user == NULL) {
		if (errno == 0) {
			return "User doesn't exist, can't have a default shell";
		}
		perror("getpwuid (for shell)");
		exit(EXIT_FAILURE);
	}
	*buf = strdup(passwd_of_user->pw_shell);
	if (*buf == NULL) {
		perror("strdup (for shell)");
		exit(EXIT_FAILURE);
	}
	return basename(*buf);
}

/*const*/ long uptime(char **buf) {
	struct sysinfo sysinfo_struct;
	(void)buf;
	if (sysinfo(&sysinfo_struct)) {
		perror("sysinfo (for uptime)");
		exit(EXIT_FAILURE);
	}
	return sysinfo_struct.uptime;
}

const char *distro(char **buf) {
	size_t linelen = 0;
	long getline_retval;
	// TODO: Use /etc/os-release instead
	FILE *fptr = fopen("/etc/issue", "r");

	if (fptr == NULL) {
		perror("Error opening file /etc/issue (for distro)");
		exit(EXIT_FAILURE);
	}
	errno = 0;
	getline_retval = getline(buf, &linelen, fptr);
	if (getline_retval == -1 && errno != 0) {
		perror("getline on file /etc/issue (for distro)");
		exit(EXIT_FAILURE);
	}
	strtok(*buf, " ");
	fclose(fptr);

	return *buf;
}
const char *hostname(char **buf) {
	int status;
	*buf = malloc(HOST_NAME_MAX + 1);
	if (*buf == NULL) {
		perror("malloc (for hostname)");
		exit(EXIT_FAILURE);
	}
	status = gethostname(*buf, HOST_NAME_MAX + 1);
	if (status == 0) {
		// if this fails we ignore it, it's just a slight waste of memory
		char *tmp = realloc(*buf, strlen(*buf));
		if (tmp != NULL)
			*buf = tmp;
		return *buf;
	}
	return "(unknown)";
}

const char *kernel(char **buf) {
	struct utsname buffer;
	if (uname(&buffer) == 0) {
		*buf = strdup(buffer.release);
		if (*buf == NULL) {
			perror("strdup (for kernel)");
			exit(EXIT_FAILURE);
		}
		return *buf;
	} else {
		return "(unknown)";
	}
}

void display(void) {
	char *uptime_buf = NULL;
	char *shell_buf = NULL;
	char *distro_buf = NULL;
	char *hostname_buf = NULL;
	char *kernel_buf = NULL;

	printf("(\\_/)\t\033[0;33m uptime: %li\n\033[0;0m",
		   uptime(&uptime_buf)); // uptime  - orange
	printf("(oᴥo)\t\033[0;31m shell: %s\n\033[0;0m",
		   shell(&shell_buf)); // shell   - red
	printf("|U°U|\t\033[0;35m distro: %s\n\033[0;0m",
		   distro(&distro_buf)); // distro  - purple
	printf("|   |\t\033[0;34m hostname: %s\n\033[0;0m",
		   hostname(&hostname_buf)); // host    - blue
	printf("'U_U'\t\033[0;36m kernel: %s\n\033[0;0m",
		   kernel(&kernel_buf)); // kernel  - cyan
	printf("  U\n");

	free(uptime_buf);
	free(shell_buf);
	free(distro_buf);
	free(hostname_buf);
	free(kernel_buf);
}
