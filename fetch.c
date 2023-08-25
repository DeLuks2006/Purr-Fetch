#include <stdio.h>
#include <stdlib.h>

// hostname 4 - read file /etc/hostname
// kernel 5 - read file or osInfo.sysname 
// ascii art 0

#define reset \x1b[0;0m

const char* uptime();
const char* shell();
const char* distro();

int main(){
  printf("uptime: %s\nshell: %s\ndistro: %s", uptime(), shell(), distro());
  return 0;
}
const char* shell(){
  const char shell = getenv("SHELL"); // ignore this, idk how to fetch the shell
  return shell;
}


const char* uptime(){
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

const char* distro(){
  static char sDistro[100];
  FILE *fptr = fopen("/etc/issue", "r");

  if (fptr == NULL)
    printf("Error opening file :(\n");
    exit(1);
  
  fscanf(fptr, "%s",sDistro);
  fclose(fptr);
  return sDistro;
}
const char* hostname(){
  static char sHost[50] = ;
  int status = gethostname(sHost, sizeof(hostname));
  if (status == 0)
    return sHost;

  return "";
}

const char* kernel(){
  // TODO: gotta learn structs and make this
}



/*void display(){
  printf("(\\_/)");// uptime  - orange
  printf("(oᴥo)"); // shell   - red
  printf("|U°U|"); // distro  - purple
  printf("|   |"); // host    - blue
  printf("'U_U'"); // kernel  - cyan
  printf("  U");
}*/
