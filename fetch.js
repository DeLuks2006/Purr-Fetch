const uptime_file = Bun.file("/proc/uptime");
const uptime_text = await uptime_file.text();
const uptime_secs = parseFloat(uptime_text.split(' ')[0]);
const uptime = new Date(1000 * uptime_secs).toISOString().substring(11, 23);

const shell = Bun.env.SHELL;

const distro_file = Bun.file("/etc/os-release");
const distro_text = await distro_file.text();
var distro = ""
distro_text.split('\n').forEach(element => {
    const vals = element.split('=');
    if (vals[0] == "PRETTY_NAME") {
        distro = vals[1].substring(1, vals[1].length - 1)
    }
});

const kernel_file = Bun.file("/proc/version");
const kernel_text = await kernel_file.text();
const kernel = kernel_text.split('(')[0];


const hostname_file = Bun.file("/etc/hostname");
const hostname_text = await hostname_file.text();
const hostname = hostname_text.trim();

console.log()
console.log(`(\\_/) \x1b[0;33m     uptime:      ${uptime}\x1b[0;0m`);
console.log(`(oᴥo) \x1b[0;31m     shell:       ${shell}\x1b[0;0m`);
console.log(`|U°U| \x1b[0;35m     distro:      ${distro}\x1b[0;0m`);
console.log(`|   | \x1b[0;34m     hostname:    ${hostname}\x1b[0;0m`);
console.log(`'U_U' \x1b[0;36m     kernel:      ${kernel}\x1b[0;0m`);
console.log(`  U`);
