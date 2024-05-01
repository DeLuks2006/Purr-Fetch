.DEFAULT_GOAL := fetch

make:
	@mkdir make

.PHONY : make/secondsfull
make/secondsfull: make $(abspath /proc/uptime) 
	@cat /proc/uptime | cut -d '.' -f1 > make/secondsfull

make/seconds: make/secondsfull make
	@cat make/secondsfull | awk '{ printf "%s", int($$1%60) }' > make/seconds

make/minutesfull: make/secondsfull make
	@cat make/secondsfull | awk '{ printf "%s", int($$1/60) }' > make/minutesfull

make/minutes: make/minutesfull make
	@cat make/minutesfull | awk '{ printf "%s", int($$1%60) }' > make/minutes

make/hours: make/minutesfull make
	@cat make/minutesfull | awk '{ printf "%s", int($$1/60) }' > make/hours

make/kernel: $(abspath /proc/version) make
	@cat /proc/version | cut -d' ' -f 1-3 > make/kernel

make/distro: $(abspath /etc/os-release) make
	@grep PRETTY_NAME /etc/os-release | cut -d'"' -f2 > make/distro

make/hostname: $(abspath /etc/hostname) make
	@head -n 1 /etc/hostname > make/hostname

fetch: make/hours make/minutes make/seconds make/kernel make/distro make/hostname
	@printf "\n(\\_/) \033[0;33m     uptime:      %02d:%02d:%02d\033[0;0m\n" "$$(cat make/hours)" "$$(cat make/minutes)" "$$(cat make/seconds)"
	@printf "(oᴥo) \033[0;31m     shell:       %s\033[0;0m\n" "$$SHELL"
	@printf "|U°U| \033[0;35m     distro:      %s\033[0;0m\n" "$$(cat make/distro)"
	@printf "|   | \033[0;34m     hostname:    %s\033[0;0m\n" "$$(cat make/hostname)"
	@printf "'U_U' \033[0;36m     kernel:      %s\033[0;0m\n" "$$(cat make/kernel)"
	@printf "  U\n"

.PHONY: clean
clean:
	rm -rf make