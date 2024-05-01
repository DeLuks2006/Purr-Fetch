#!/usr/bin/env bash

uptime="$(awk '{m=$1/60; h=m/60; printf "%s:%s:%s", int(h%24), int(m%60), int($1%60) }' /proc/uptime)"
distro="$(grep PRETTY_NAME /etc/os-release | cut -d'"' -f2)"
hostname="$(head -n 1 /etc/hostname)"
kernel="$(awk '{printf "%s %s %s", $1, $2, $3}' /proc/version)"

printf "\n(\\_/) \033[0;33m     uptime:      %s\033[0;0m\n" "$uptime"
printf "(oᴥo) \033[0;31m     shell:       %s\033[0;0m\n" "$SHELL"
printf "|U°U| \033[0;35m     distro:      %s\033[0;0m\n" "$distro"
printf "|   | \033[0;34m     hostname:    %s\033[0;0m\n" "$hostname"
printf "'U_U' \033[0;36m     kernel:      %s\033[0;0m\n" "$kernel"
printf "  U\n"
