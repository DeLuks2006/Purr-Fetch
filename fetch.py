#!usr/bin/python3
# -- welcome to this bloated mess --

import time 
import datetime
from os import environ
import platform

#shell
shell = environ['SHELL'] # /bin/bash

# uptime
uptime=time.clock_gettime(time.CLOCK_BOOTTIME)
up=str(datetime.timedelta(seconds=uptime)) # 0:00:00.000000

# hostname
with open("/etc/hostname", "r") as host:
    # With blocks ensure that the file will get closed
    hostname = host.read().strip()

# distro
with open("/etc/issue", "r") as distro:
    distrob = distro.read().strip().replace("(\l)","").replace("\\r","")

# kernel
kernel = platform.release()

#terminal
# terminal = os.ctermid()

def structure():
    print("\n(\_/) \033[0;33m     uptime:      %s\033[0;0m" % (up)) #orange
    print("(oᴥo) \033[0;31m     shell:       %s\033[0;0m" % (shell)) #red
    print("|U°U| \033[0;35m     distro:      %s\033[0;0m" % (distrob)) #purple
    print("|   | \033[0;34m     hostname:    %s\033[0;0m" % (hostname)) #blue
    print("'U_U' \033[0;36m     kernel:      %s\033[0;0m" % (kernel)) #cyan
    print("  U" ) # dont work proprerly ## code from before i gave up the terminal detection:  \033[1;32m     terminal:    %s\033[0;0m" % (terminal)
    # terminal => os.ctermid()


structure()
