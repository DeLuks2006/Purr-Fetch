const fs = require("fs").promises;

// Function to read file asynchronously
const readFileAsync = async (path) => {
  try {
    const data = await fs.readFile(path, "utf8");
    return data;
  } catch (err) {
    console.error("Error reading file:", err);
    throw err;
  }
};

// Function to parse /proc/uptime
const getUptime = async () => {
  const uptimeText = await readFileAsync("/proc/uptime");
  const uptimeSecs = parseFloat(uptimeText.split(" ")[0]);
  const uptime = new Date(1000 * uptimeSecs).toISOString().substring(11, 23);
  return uptime;
};

// Function to parse /etc/os-release
const getDistro = async () => {
  const distroText = await readFileAsync("/etc/os-release");
  const lines = distroText.split("\n");
  let distro = "";
  for (const line of lines) {
    const [key, value] = line.split("=");
    if (key === "PRETTY_NAME") {
      distro = value.substring(1, value.length - 1);
      break; // No need to continue searching
    }
  }
  return distro;
};

// Function to parse /proc/version
const getKernel = async () => {
  const kernelText = await readFileAsync("/proc/version");
  const kernel = kernelText.split("(")[0].trim();
  return kernel;
};

// Function to parse /etc/hostname
const getHostname = async () => {
  const hostnameText = await readFileAsync("/etc/hostname");
  const hostname = hostnameText.trim();
  return hostname;
};

(async () => {
  try {
    const uptime = await getUptime();
    const shell = process.env.SHELL;
    const distro = await getDistro();
    const kernel = await getKernel();
    const hostname = await getHostname();

    console.log();
    console.log(`(\\_/) \x1b[0;33m     uptime:      ${uptime}\x1b[0;0m`);
    console.log(`(oᴥo) \x1b[0;31m     shell:       ${shell}\x1b[0;0m`);
    console.log(`|U°U| \x1b[0;35m     distro:      ${distro}\x1b[0;0m`);
    console.log(`|   | \x1b[0;34m     hostname:    ${hostname}\x1b[0;0m`);
    console.log(`'U_U' \x1b[0;36m     kernel:      ${kernel}\x1b[0;0m`);
    console.log(`  U`);
  } catch (err) {
    console.error("Error:", err);
  }
})();
