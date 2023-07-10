# -- welcome to this bloated mess --

import time 
import datetime
from os import environ
import os
import platform

#shell
shell = environ['SHELL'] # /bin/bash

# uptime
uptime=time.clock_gettime(time.CLOCK_BOOTTIME)
up=str(datetime.timedelta(seconds=uptime)) # 0:00:00.000000

# hostname
host = open("/etc/hostname", "r")
hostname = host.read()
hostname = hostname.strip()

# distro
distro = open("/etc/issue", "r")
distrob = distro.read()
distrob = distrob.strip()
distrob = distrob.replace("(\l)","")
distrob = distrob.replace("\\r","")

# kernel
kernel = platform.release()

#terminal
# terminal = os.ctermid()

def structure():
    print(f"\n(\_/) \033[0;33m     uptime:      %s\033[0;0m" % (up)) #orange
    print(f"(oᴥo) \033[0;31m     shell:       %s\033[0;0m" % (shell)) #red
    print(f"|U°U| \033[0;35m     distro:      %s\033[0;0m" % (distrob)) #purple
    print(f"|   | \033[0;34m     hostname:    %s\033[0;0m" % (hostname)) #blue
    print(f"'U_U' \033[0;36m     kernel:      %s\033[0;0m" % (kernel)) #cyan
    # print(f"  U   \033[1;32m     terminal:    %s\033[0;0m" % (terminal)) # dont work proprerly
    # terminal => os.ctermid()


structure()
