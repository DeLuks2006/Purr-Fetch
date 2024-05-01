package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

func uptime() string {
	dat, err := os.ReadFile("/proc/uptime")
	if err != nil {
		return ""
	}

	bef, _, _ := strings.Cut(string(dat), " ")
	f, err := strconv.ParseFloat(bef, 32)
	dur := time.Duration(f * float64(time.Second)).Round(time.Second)

	return dur.String()
}

func shell() string {
	return os.Getenv("SHELL")
}

func distro() string {
	dat, err := os.ReadFile("/etc/os-release")
	if err != nil {
		return ""
	}

	_, nameWithTheRest, success := strings.Cut(string(dat), `PRETTY_NAME="`)
	if !success {
		return "no pretty name"
	}
	name, _, _ := strings.Cut(nameWithTheRest, `"`)

	return name
}

func hostname() string {
	dat, err := os.ReadFile("/etc/hostname")
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(dat))
}

func kernel() string {
	dat, err := os.ReadFile("/proc/version")
	if err != nil {
		return ""
	}

	parts := strings.SplitN(string(dat), " ", 4)

	return fmt.Sprintf("%s %s %s", parts[0], parts[1], parts[2])
}

func main() {
	fmt.Printf("\n(\\_/) \033[0;33m     uptime:      %s\033[0;0m\n", uptime())
	fmt.Printf("(oᴥo) \033[0;31m     shell:       %s\033[0;0m\n", shell())
	fmt.Printf("|U°U| \033[0;35m     distro:      %s\033[0;0m\n", distro())
	fmt.Printf("|   | \033[0;34m     hostname:    %s\033[0;0m\n", hostname())
	fmt.Printf("'U_U' \033[0;36m     kernel:      %s\033[0;0m\n", kernel())
	fmt.Printf("  U\n")
}
