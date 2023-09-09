#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <string.h>

// hostname 4 - read file /etc/hostname
// kernel 5 - read file or osInfo.sysname 
// ascii art 0


void display(void);
const char* uptime(void);
const char* shell(void);
const char* distro(void);
const char* hostname(void);
const char* kernel(void);

int main(void){
  display();
  return 0;
}
const char* shell(void){
  const char* shell = getenv("SHELL"); 
  return shell;
}


const char* uptime(void){
  static char sTime[300];
  FILE *fptr = fopen("/proc/uptime", "r");
  
  if (fptr == NULL){
    printf("Error opening file :(\n");
    exit(1); // exit if file pointer returns NULL
  }

  fscanf(fptr,"%s", sTime);
  fclose(fptr);
  return sTime;
}

const char* distro(void){
  static char sDistro[100];
  FILE *fptr = fopen("/etc/issue", "r");

  if (fptr == NULL){
    printf("Error opening file :(\n");
    exit(1);
  }
  fscanf(fptr, "%s",sDistro);
  fclose(fptr);
  return sDistro;
}
const char* hostname(void){
  static char sHost[50];
  int status = gethostname(sHost, sizeof(sHost));
  if (status == 0){
    return sHost;
  }
  return "";
}

const char* kernel(void){
  struct utsname buffer;
  if (uname(&buffer) == 0){
    return strdup(buffer.release);
  } else {
    return "";
  }
}



void display(void){
  printf("(\\_/)\t\033[0;33m uptime: %s\n\033[0;0m", uptime());// uptime  - orange
  printf("(oᴥo)\t\033[0;31m shell: %s\n\033[0;0m", shell()); // shell   - red
  printf("|U°U|\t\033[0;35m distro: %s\n\033[0;0m", distro()); // distro  - purple
  printf("|   |\t\033[0;34m hostname: %s\n\033[0;0m", hostname()); // host    - blue
  printf("'U_U'\t\033[0;36m kernel: %s\n\033[0;0m", kernel()); // kernel  - cyan
  printf("  U\n");
}
